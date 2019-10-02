#pragma once
#include "Grass.h"

class GRASSCURSOR {
	friend void InitGame();
public:
	enum CursorState {
		up,
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