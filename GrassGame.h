#pragma once
#include "Grass.h"

class GRASSCURSOR {
	friend const void GRASSGAME::initGame();
public:
	enum CursorState {
		bothUp,
		leftDown,
		rightDown,
		bothDown,
	};
private:
	static Lawn currentLawn;
	static CursorState lastStatus;
public:

	const static CursorState updateCrusorState();
	const static CursorState getLastCursorState();
	const static Lawn& getCurrentLawn();

	const static Lawn& setCurrentLawn(const Lawn& lawn2);

	static void JudgeCommand();
};

extern GRASSCURSOR GrassCursor;

class GRASSGAME {
private:
	const static void initGame();
	const static bool win();
	const static void celebrate();
public:
	const static void start();
};

extern GRASSGAME GrassGame;