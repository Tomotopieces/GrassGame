#include <iostream>
#include <thread>
#include <chrono>
#include "GrassGameFunction.h"
#include "GrassGameData.h"
#include "ThreadPool.h"

// Initialization
std::mutex GRASSGAMEFUNCTION::GrassMutex;
bool GRASSGAMEFUNCTION::mouseLeftClick = false;
bool GRASSGAMEFUNCTION::mouseRightClick = false;
bool GRASSGAMEFUNCTION::mouseBothClick = false;
Lawn GRASSGAMEFUNCTION::currentLawn = Lawn(0,0,0);
time_t GRASSGAMEFUNCTION::timer = time(NULL);

const Lawn& GRASSGAMEFUNCTION::getCurrentLawn()
{
	return currentLawn;
}

const Lawn& GRASSGAMEFUNCTION::setCurrentLawn(const Lawn& lawn2)
{
	currentLawn = lawn2;
	return currentLawn;
}

GRASSGAMEFUNCTION::MouseState GRASSGAMEFUNCTION::getMouseState()
{
	std::unique_lock<std::mutex> lock(GrassMutex);
	if (Mouse.leftDown())
		return leftDown;
	else if (Mouse.rightDown())
		return rightDown;
	else if (Mouse.bothDown())
		return bothDown;
	else return bothUp;
}

void GRASSGAMEFUNCTION::centered(std::string text, int offsetX, int offsetY)
{
	Cursor.setPosition((GrassGameData::ConsoleWidth - text.size()) / 2 + offsetX, GrassGameData::ConsoleHeight / 2 + offsetY);
	std::cout << text;
}

void GRASSGAMEFUNCTION::initGame()
{
	Screen.setSize(GrassGameData::ConsoleWidth, GrassGameData::ConsoleHeight);
	Screen.hideScrollBar();
	Screen.setTitle("Grass Game!");
	Cursor.hide();
	currentLawn = welcome;
	currentLawn.Draw();
}

const bool GRASSGAMEFUNCTION::win()
{
	return currentLawn.getGrassList().size() == 0;
}

void GRASSGAMEFUNCTION::celebrate()
{
	Character.setBackColor(0);
	Character.setForeColor(white + light);
	centered("You Win!", 0, -2);
	centered("Press any key to exit.", 0, 1);
}

void GRASSGAMEFUNCTION::start()
{
	initGame();
	auto MousePositionThread = std::async(std::launch::async,
		[]() {
			Point lastPos = { 0,0 };
			while (!win()) {
				if (lastPos == Mouse.getPosition())
					continue;
				
				Cursor.setPosition(lastPos);
				Character.setBackColor(0);
				currentLawn.getPoint(lastPos).Draw();

				lastPos = Mouse.getPosition();
				Character.setBackColor(white);
				Cursor.setPosition(lastPos);
				currentLawn.getPoint(lastPos).Draw();
			}
			Cursor.setPosition(lastPos);
			Character.setBackColor(0);
			currentLawn.getPoint(lastPos).Draw();
		}
	);
	auto MouseEventThread = std::async(std::launch::async,
		[]() {
			auto lastState = bothUp;
			while (!win()) {
				switch (lastState) {
					case leftDown:
						lastState = getMouseState();
						switch (lastState) {
							case bothUp:
								mouseLeftClick = true;
								break;
							case rightDown:
								break;
							case bothDown:
								break;
							default:
								break;
						}
						break;
					case rightDown:
						lastState = getMouseState();
						break;
					case bothDown:
						lastState = getMouseState();
						break;
					default:
						lastState = getMouseState();
						break;
				}
			}
		}
	);
	auto judgeMouseEvent = std::async(std::launch::async,
		[]() {
			while (!win()) {
				if (mouseLeftClick) {
					mouseLeftClick = false;
					currentLawn.unmakeGrass(Mouse.getPosition());
				}
			}
		}
	);
	MousePositionThread.wait();
	MouseEventThread.wait();
	judgeMouseEvent.wait();
	celebrate();
	getchar();
}

GRASSGAMEFUNCTION GrassGameFunction;