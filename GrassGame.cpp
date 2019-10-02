#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GrassGame.h"

GRASSGAME::CursorState GRASSGAME::lastStatus = GRASSGAME::CursorState::bothUp;
Point GRASSGAME::lastPos = Point(Mouse.getPosition());
Lawn GRASSGAME::currentLawn = Lawn(0,0,0);
time_t GRASSGAME::timer = time(NULL);

const GRASSGAME::CursorState GRASSGAME::updateCrusorState()
{
	if (Mouse.leftDown())
		lastStatus = leftDown;
	else if (Mouse.rightDown())
		lastStatus = rightDown;
	else if (Mouse.bothDown())
		lastStatus = bothDown;
	else lastStatus = bothUp;
	return lastStatus;
}

const GRASSGAME::CursorState GRASSGAME::getLastCursorState()
{
	return lastStatus;
}

const Lawn& GRASSGAME::getCurrentLawn()
{
	return currentLawn;
}

const void GRASSGAME::cursorStyle()
{
	if (lastPos == Mouse.getPosition())
		return;
	Character.setBackColor(0);
	currentLawn.getPoint(lastPos).Draw();

	Character.setBackColor(light);
	lastPos = Mouse.getPosition();
	currentLawn.getPoint(lastPos).Draw();
}

const Lawn& GRASSGAME::setCurrentLawn(const Lawn& lawn2)
{
	currentLawn = lawn2;
	return currentLawn;
}

const void GRASSGAME::judgeCommand()
{
	switch (lastStatus) {
		case bothUp:
			updateCrusorState();
			switch (lastStatus) {
				case bothUp:
					break;
				case leftDown:
					currentLawn.unmakeGrass(Mouse.getPosition());
					break;
				case rightDown:
					break;
				case bothDown:
					break;
				default:
					break;
			}
			break;
		case leftDown:
			updateCrusorState();
			break;
		case rightDown:
			updateCrusorState();
			break;
		case bothDown:
			updateCrusorState();
			break;
		default:
			updateCrusorState();
			break;
	}
}

const void GRASSGAME::centered(std::string text, int offsetX, int offsetY)
{
	Cursor.setPosition((ConsoleWidth - text.size()) / 2 + offsetX, ConsoleHeight / 2 + offsetY);
	std::cout << text;
}

const void GRASSGAME::initGame()
{
	srand((unsigned)time(NULL));
	Screen.setSize(ConsoleWidth, ConsoleHeight);
	Screen.hideScrollBar();
	Screen.setTitle("Grass Game!");
	Cursor.hide();
	currentLawn = Lawn(ConsoleWidth, ConsoleHeight, GrassCount);
}

const bool GRASSGAME::win()
{
	return currentLawn.getGrassList().size() == 0;
}

const void GRASSGAME::celebrate()
{
	Character.setBackColor(0);
	Cursor.setPosition(lastPos.getX(), lastPos.getY());
	std::cout << " ";
	Character.setForeColor(white + light);
	centered("You Win!", 0, -2);
	centered("Press any key to exit.", 0, 1);
}

const void GRASSGAME::start()
{
	initGame();
	while (!GrassGame.win()) {
		cursorStyle();
		judgeCommand();
	}
	GrassGame.celebrate();
	getchar();
}

GRASSGAME GrassGame;