#include <iostream>
#include "GrassGameCursorFunction.h"

GRASSCURSOR::CursorState GRASSCURSOR::lastStatus = GRASSCURSOR::CursorState::up;
Lawn GRASSCURSOR::currentLawn = Lawn();

const GRASSCURSOR::CursorState GRASSCURSOR::updateCrusorState()
{
	if (Mouse.leftDown())
		lastStatus = leftDown;
	else if (Mouse.rightDown())
		lastStatus = rightDown;
	else if (Mouse.bothDown())
		lastStatus = bothDown;
	else lastStatus = up;
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
		case up:
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