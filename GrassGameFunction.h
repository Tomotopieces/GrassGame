#pragma once
#include "Grass.h"

static class GRASSGAMEFUNCTION {
public:
	enum CursorState {
		bothUp,
		leftDown,
		rightDown,
		bothDown,
	};
private:

	static Lawn currentLawn;
	static Point lastPos;
	static CursorState lastStatus;
	static time_t timer;

	const static void initGame();
	const static bool win();
	const static void celebrate();

	const static CursorState updateCrusorState();
	const static CursorState getLastCursorState();
	const static Lawn& getCurrentLawn();

	const static void cursorStyle();

	const static Lawn& setCurrentLawn(const Lawn& lawn2);

	const static void judgeCommand();

	const static void centered(std::string text, int offsetX = 0, int offsetY = 0);
public:

	const static void start();
};

extern GRASSGAMEFUNCTION GrassGameFunction;