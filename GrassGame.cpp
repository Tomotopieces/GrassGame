#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GrassGame.h"

GRASSCURSOR::CursorState GRASSCURSOR::lastStatus = GRASSCURSOR::CursorState::bothUp;
Lawn GRASSCURSOR::currentLawn = Lawn();

const GRASSCURSOR::CursorState GRASSCURSOR::updateCrusorState()
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

const GRASSCURSOR::CursorState GRASSCURSOR::getLastCursorState()
{
	return lastStatus;
}

const Lawn& GRASSCURSOR::getCurrentLawn()
{
	return currentLawn;
}

const Lawn& GRASSCURSOR::setCurrentLawn(const Lawn& lawn2)
{
	currentLawn = lawn2;
	return currentLawn;
}

void GRASSCURSOR::JudgeCommand()
{
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
}

GRASSCURSOR GrassCursor;

const void GRASSGAME::initGame()
{
	srand((unsigned)time(NULL));
	Screen.setSize(ConsoleWidth, ConsoleHeight);
	Screen.hideScrollBar();
	Screen.setTitle("Grass Game!");
	Cursor.hide();
	GrassCursor.setCurrentLawn(Lawn(40));
}

const bool GRASSGAME::win()
{
	return GrassCursor.getCurrentLawn().getGrassList().size() == 0;
}

const void GRASSGAME::celebrate()
{
	Cursor.setPosition(ConsoleWidth / 2 - 4, ConsoleHeight / 2 - 1);
	Character.setForeColor(white);
	std::cout << "You Win!";
}

const void GRASSGAME::start()
{
	initGame();
	while (!GrassGame.win())
		GrassCursor.JudgeCommand();
	GrassGame.celebrate();
	getchar();
}

GRASSGAME GrassGame;