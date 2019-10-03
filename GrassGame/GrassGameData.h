#pragma once
#include "Grass.h"

static class GrassGameData {
public:
	const static int ConsoleWidth = 96;
	const static int ConsoleHeight = 27;

	const static std::vector<std::string> GrassPic1;
	const static std::vector<std::string> GrassPic2;
};

class StageData {
public:
private:

	bool dataType;	//false: CountType		true: LawnType
	union
	{
		int grassCount;
		Lawn lawn;
	};

	explicit StageData();
public:
	StageData(const int GrassCount);
	StageData(const Lawn& lawn2);
	StageData(const StageData& data2);
	StageData(StageData&& data2);
	~StageData() {}
	const StageData& operator=(const StageData& data2);
	const StageData& operator=(const Lawn& lawn2);
	const bool operator==(const StageData& data2);

	const bool getDataType()const;

	operator Lawn()const;
};

typedef StageData Location;

extern Location welcome;