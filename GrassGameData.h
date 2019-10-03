#pragma once
#include "Grass.h"

class StageData {
private:
	const static int ConsoleWidth = 96;
	const static int ConsoleHeight = 27;

	bool dataType;	//false: CountType		true: LawnType
	union
	{
		int grassCount;
		Lawn lawn;
	};

	explicit StageData();
	~StageData() {}
public:
	StageData(const int GrassCount);
	StageData(const Lawn& lawn2);
	StageData(const StageData& data2);
	StageData(StageData&& data2);
	const StageData& operator=(const StageData& data2);
	const bool operator==(const StageData& data2);
};

typedef StageData Location;