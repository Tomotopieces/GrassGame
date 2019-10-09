#pragma once
#include "Grass.h"
#include <ppltasks.h>
#include <mutex>

class GRASSGAMEFUNCTION {
public:
	enum MouseState {
		bothUp,
		leftDown,
		rightDown,
		bothDown,
	};
private:
	static std::mutex GrassMutex;
	
	static bool mouseLeftClick;
	static bool mouseRightClick;
	static bool mouseBothClick;
	static Lawn currentLawn;
	static time_t timer;

	const static Lawn& getCurrentLawn();
	const static Lawn& setCurrentLawn(const Lawn& lawn2);

	static void initGame();
	const static bool win();
	static void celebrate();

	static MouseState getMouseState();
	static void centered(std::string text, int offsetX = 0, int offsetY = 0);
public:
	static void start();
};

extern GRASSGAMEFUNCTION GrassGameFunction;