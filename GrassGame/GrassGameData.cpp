#include "GrassGameData.h"

const std::vector<std::string> GrassGameData::GrassPic1 = { "/", "\\", "`", "~", "-", "^" };
const std::vector<std::string> GrassGameData::GrassPic2 = { "v", "V", "y", "Y", ">", "#" };

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

const StageData& StageData::operator=(const Lawn& lawn2)
{
	lawn = lawn2;
	return*this;
}

const bool StageData::operator==(const StageData& data2)
{
	if (dataType)
		return grassCount == data2.grassCount;
	return lawn == data2.lawn;
}

const bool StageData::getDataType() const
{
	return dataType;
}

StageData::operator Lawn() const
{
	if (dataType)
		return lawn;
	else
		return Lawn(GrassGameData::ConsoleWidth, GrassGameData::ConsoleHeight, grassCount);
}

Location welcome = Lawn(GrassGameData::ConsoleWidth, GrassGameData::ConsoleHeight, 5);
