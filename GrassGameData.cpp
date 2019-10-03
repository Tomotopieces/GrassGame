#include "GrassGameData.h"

StageData::StageData(const int GrassCount)
	:dataType(false), grassCount(GrassCount)
{
}

StageData::StageData(const Lawn& lawn2)
	:dataType(true), lawn(lawn2)
{
}

StageData::StageData(const StageData& data2)
	:dataType(data2.dataType)
{
	if (dataType)
		lawn = data2.lawn;
	else
		grassCount = data2.grassCount;
}

StageData::StageData(StageData&& data2)
	:dataType(data2.dataType)
{
	if (dataType)
		lawn = data2.lawn;
	else
		grassCount = data2.grassCount;
	data2.~StageData();
}

const StageData& StageData::operator=(const StageData& data2)
{
	dataType = data2.dataType;
	if (dataType)
		lawn = data2.lawn;
	else
		grassCount = data2.grassCount;
	return*this;
}

const bool StageData::operator==(const StageData& data2)
{
	if (dataType)
		return grassCount == data2.grassCount;
	return lawn == data2.lawn;
}
