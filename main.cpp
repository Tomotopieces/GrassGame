#include <iostream>
#include <exception>
#include "GrassGameCursorFunction.h"
using namespace ConsoleFunction;

int main() {
	InitGame();
	while (1) {
		GrassCursor.JudgeCommand();
	}
	return 0;
}