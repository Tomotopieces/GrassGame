#include <iostream>
#include "GrassGameFunction.h"
#include "GrassGameData.h"

GRASSGAMEFUNCTION::CursorState GRASSGAMEFUNCTION::lastStatus = GRASSGAMEFUNCTION::CursorState::bothUp;
Point GRASSGAMEFUNCTION::lastPos = Point(Mouse.getPosition());
Lawn GRASSGAMEFUNCTION::currentLawn = Lawn(0,0,0);
time_t GRASSGAMEFUNCTION::timer = time(NULL);

const GRASSGAMEFUNCTION::CursorState GRASSGAMEFUNCTION::updateCrusorState()
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

const GRASSGAMEFUNCTION::CursorState GRASSGAMEFUNCTION::getLastCursorState()
{
	return lastStatus;
}

const Lawn& GRASSGAMEFUNCTION::getCurrentLawn()
{
	return currentLawn;
}

const void GRASSGAMEFUNCTION::cursorStyle()
{
	if (lastPos == Mouse.getPosition())
		return;
	Character.setBackColor(0);
	currentLawn.getPoint(lastPos).Draw();

	Character.setBackColor(light);
	lastPos = Mouse.getPosition();
	currentLawn.getPoint(lastPos).Draw();
}

const Lawn& GRASSGAMEFUNCTION::setCurrentLawn(const Lawn& lawn2)
{
	currentLawn = lawn2;
	return currentLawn;
}

const void GRASSGAMEFUNCTION::judgeCommand()
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

const void GRASSGAMEFUNCTION::centered(std::string text, int offsetX, int offsetY)
{
	Cursor.setPosition((GameData::ConsoleWidth - text.size()) / 2 + offsetX, GameData::ConsoleHeight / 2 + offsetY);
	std::cout << text;
}

const void GRASSGAMEFUNCTION::initGame()
{
	Screen.setSize(GameData::ConsoleWidth, GameData::ConsoleHeight);
	Screen.hideScrollBar();
	Screen.setTitle("Grass Game!");
	Cursor.hide();
	currentLawn = welcome;
	Point pos(1, 2);
}

const bool GRASSGAMEFUNCTION::win()
{
	return currentLawn.getGrassList().size() == 0;
}

const void GRASSGAMEFUNCTION::celebrate()
{
	Character.setBackColor(0);
	Cursor.setPosition(lastPos.getX(), lastPos.getY());
	std::cout << " ";
	Character.setForeColor(white + light);
	centered("You Win!", 0, -2);
	centered("Press any key to exit.", 0, 1);
}

const void GRASSGAMEFUNCTION::start()
{
	initGame();
	while (!GrassGameFunction.win()) {
		cursorStyle();
		judgeCommand();
	}
	GrassGameFunction.celebrate();
	getchar();
}

GRASSGAMEFUNCTION GrassGameFunction;