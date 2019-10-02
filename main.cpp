#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GrassGameCursorFunction.h"
using namespace ConsoleFunction;

void InitGame();

int main() {
	InitGame();
	while (GrassCursor.getCurrentLawn().getGrassList().size())
		GrassCursor.JudgeCommand();
	Cursor.setPosition(ConsoleWidth / 2 - 4, ConsoleHeight / 2 - 1);
	Character.setForeColor(white);
	std::cout << "You Win!";
	getchar();
	return 0;
}

void InitGame()
{
	srand((unsigned)time(NULL));
	Screen.setSize(ConsoleWidth, ConsoleHeight);
	Screen.hideScrollBar();
	Screen.setTitle("Grass Game!");
	Cursor.hide();
	GrassCursor.currentLawn = Lawn(20);
}