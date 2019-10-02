#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Grass.h"
#include "ConsoleFunc.h"
#pragma comment(lib, "ConsoleFunc.lib")
using namespace ConsoleFunction;

void Grass::setPic()
{
	if (count == 0)
		grassPic = " ";
	if (count == 1)
		grassPic = GrassPic1[rand() % GrassPic1.size()];
	if (count == 2)
		grassPic = GrassPic2[rand() % GrassPic2.size()];
}

Grass::Grass() {
	point = Point(0, 0);
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
	count = rand() % 2 + 1;
	setPic();
}

Grass::Grass(const int x, const int y)
	:point(x, y)
{
	count = rand() % 2 + 1;
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

const bool Grass::operator==(const Grass& grass)const
{
	return point == grass.point && count == grass.count;
}

void Grass::Draw()const
{
	Cursor.setPosition(point.getX(), point.getY());
	Character.setForeColor(green + light);
	std::cout << grassPic;
}

void Lawn::set0Position()
{
	for (int x = 0; x < getWidth(); ++x) {
		for (int y = 0; y < getHeight(); ++y) {
			setPoint(x, y, Grass(x, y, 0));
		}
	}
}

Lawn::Lawn(int width, int height)
	:GameMap<Grass>(width, height)
{
	set0Position();
}

Lawn::Lawn(int width, int height, int grassCount)
	:GameMap<Grass>(width, height)
{
	set0Position();
	makeGrass(grassCount);
}

Lawn::Lawn(Lawn& lawn2)
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
	setMap(lawn2);
	setWidth(lawn2.getWidth());
	setHeight(lawn2.getHeight());
	grassList = lawn2.grassList;
	return*this;
}

const std::vector<Grass>& Lawn::getGrassList() const
{
	return grassList;
}

const Lawn& Lawn::makeGrass(int grassCount)
{
	for (int i = 0; i < grassCount; ++i)
	{
		Grass grass(rand() % getWidth(), rand() % getHeight(), rand() % 2 + 1);
		if(grassList.size())
			for (auto it = grassList.begin(); it != grassList.end(); ++it) {
				if (it->getPosition() == grass.getPosition()) {
					grass.getPosition().ReSet(getWidth(), getHeight());
					it = grassList.begin();
				}
			}
		plantGrass(grass);
	}
	return*this;
}

const Lawn& Lawn::plantGrass(Grass& grass)
{
	grassList.push_back(grass);
	grass.Draw();
	this->setPoint(grass.getPosition(), grass);
	return*this;
}

const Lawn& Lawn::unmakeGrass(Point pos)
{
	if (this->getPoint(pos).getCount() == 0)
		return*this;
	for (auto it = grassList.begin(); it != grassList.end(); ++it) {
		if (it->getPosition() == pos) {
			grassList.erase(it);
			break;
		}
	}
	this->setPoint(pos, Grass(pos, 0));
	getPoint(pos).Draw();
	return*this;
}

const Lawn& Lawn::unmakeGrass(Grass& grass, bool all)
{
	if (grass.getCount() == 0)
		return*this;
	for (auto it = grassList.begin(); it != grassList.end(); ++it) {
		if (*it == grass) {
			grassList.erase(it);
			if (!all)
				break;
		}
	}
	Point pos = grass.getPosition();
	this->setPoint(pos, Grass(pos, 0));
	getPoint(pos).Draw();
	return*this;
}

const Lawn& Lawn::Draw() const
{
	for (Grass grass : grassList)
		grass.Draw();
	return*this;
}
