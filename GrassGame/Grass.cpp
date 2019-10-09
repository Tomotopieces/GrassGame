#include <iostream>
#include "Grass.h"
#include "GrassGameData.h"
#include "ConsoleFunc.h"
#pragma comment(lib, "ConsoleFunc.lib")
using namespace ConsoleFunction;

void Grass::setPic()
{
	if (count == 0)
		grassPic = " ";
	if (count == 1)
		grassPic = GrassGameData::GrassPic1[Rand() % GrassGameData::GrassPic1.size()];
	if (count == 2)
		grassPic = GrassGameData::GrassPic2[Rand() % GrassGameData::GrassPic2.size()];
}

Grass::Grass() {
	point = Point(-1, -1);
	count = 0;
	grassPic = " ";
}

Grass::Grass(const Grass& grass2)
	:point(grass2.point), count(grass2.count), grassPic(grass2.grassPic)
{
}

Grass::Grass(Grass&& grass2)
	:point(grass2.point), count(grass2.count), grassPic(grass2.grassPic)
{
	grass2.~Grass();
}

Grass::Grass(const Point pos)
	:point(pos)
{
	count = Rand() % 2 + 1;
	setPic();
}

Grass::Grass(const int x, const int y)
	:point(x, y)
{
	count = Rand() % 2 + 1;
	setPic();
}

Grass::Grass(const Point pos, const int Count)
	:count(Count), point(pos)
{
	setPic();
}

Grass::Grass(const int x, const int y, const int Count)
	:count(Count), point(x, y)
{
	setPic();
}

Grass& Grass::operator=(const Grass& grass2)
{
	point = grass2.point;
	count = grass2.count;
	grassPic = grass2.grassPic;
	return*this;
}

const bool Grass::operator==(const Grass& grass)const
{
	return point == grass.point && count == grass.count;	//不判断图案是否一样
}

const bool Grass::operator!=(const Grass& grass) const
{
	return !operator==(grass);
}

Point Grass::getPosition()const
{
	return point;
}

const int Grass::getCount() const
{
	return count;
}

const std::string Grass::getGrassPic() const
{
	return grassPic;
}

void Grass::Draw()const
{
	Cursor.setPosition(point.getX(), point.getY());
	Character.setForeColor(green + light);
	std::cout << grassPic;
}

void Lawn::set0Position()
{
	for (int x = 0; x < getWidth(); ++x)
		for (int y = 0; y < getHeight(); ++y)
			if (This[x][y].getCount() == 0)
				This.setPoint(x, y, Grass(x, y, 0));
}

Lawn::Lawn(const int width, const int height)
	:GameMap<Grass>(width, height)
{
	set0Position();
}

Lawn::Lawn(const int width, const int height, const std::vector<Grass> GrassList)
	:GameMap(width, height), grassList(GrassList)
{
	set0Position();
}

Lawn::Lawn(const int width, const int height, const int grassCount)
	:GameMap<Grass>(width, height)
{
	set0Position();
	makeGrass(grassCount);
}

Lawn::Lawn(const Lawn& lawn2)
	:GameMap(lawn2), grassList(lawn2.grassList)
{
}

Lawn::Lawn(Lawn&& lawn2)
	:GameMap(lawn2), grassList(lawn2.grassList)
{
	lawn2.~Lawn();
}

const Lawn& Lawn::operator=(const Lawn& lawn2)
{
	GameMap::operator=(lawn2);
	grassList = lawn2.grassList;
	return This;
}

const bool Lawn::operator==(const Lawn& lawn2)const
{
	if (grassList.size() != lawn2.grassList.size())
		return false;
	for (int i = 0; i < grassList.size(); ++i)
		if (grassList[i] != lawn2.grassList[i])
			return false;
	return true;
}

const bool Lawn::operator!=(const Lawn& lawn2)const
{
	return !operator==(lawn2);
}

const std::vector<Grass>& Lawn::getGrassList() const
{
	return grassList;
}

const Lawn& Lawn::makeGrass(int grassCount)
{
	for (int i = 0; i < grassCount; ++i)
	{
		Grass grass(Rand() % getWidth(), Rand() % getHeight(), Rand() % 2 + 1);
		if(grassList.size())
			for (auto it = grassList.begin(); it != grassList.end(); ++it) {
				if (it->getPosition() == grass.getPosition()) {
					grass.getPosition().ReSet(getWidth(), getHeight());
					it = grassList.begin();
				}
			}
		plantGrass(grass);
	}
	return This;
}

const Lawn& Lawn::plantGrass(Grass& grass)
{
	if (grass.getPosition().exist()) {
		grassList.push_back(grass);
		This.setPoint(grass.getPosition(), grass);
		This.setPoint(grass.getPosition(), grass);
	}
	return This;
}

const Lawn& Lawn::unmakeGrass(Point pos)
{
	if (pos.exist() && This[pos].getCount() == 0)
		return This;
	grassList.erase(std::find(grassList.begin(), grassList.end(), Grass(pos, This[pos].getCount())));
	This.setPoint(pos, Grass(pos, 0));
	This[pos].Draw();
	return This;
}

const Lawn& Lawn::unmakeGrass(Grass& grass)
{
	if (grass.getPosition().exist() && grass.getCount() == 0)
		return This;
	Point pos = find(grass);
	grassList.erase(std::find(grassList.begin(), grassList.end(), grass));
	This.setPoint(pos, Grass(pos, 0));
	This[pos].Draw();
	return This;
}

const Lawn& Lawn::Draw() const
{
	for (Grass grass : grassList)
		grass.Draw();
	return This;
}

void DrawGrass(const Lawn& lawn, int x, int y)
{
	lawn[x][y].Draw();
}

void DrawGrass(const Lawn& lawn, Point pos)
{
	lawn[pos].Draw();
}
