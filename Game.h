#pragma once
#include <vector>
#include "ConsoleFunc.h"
#pragma comment(lib, "ConsoleFunc.lib")
using namespace ConsoleFunction;

//坐标
class Point {
private:
	int x;
	int y;
public:
	Point();
	Point(const Point& pos2);
	Point(const COORD& pos2);
	Point(Point&& pos2);
	Point(const int X, const int Y);
	Point& operator=(const Point& pos2);
	Point& operator=(const COORD& pos2);

	const int getX()const;
	const int getY()const;

	//同位置判定
	const bool operator==(const Point& pos2)const;

	//重骰坐标
	void ReSet(const int MaxWidth, const int MaxHeight);
};

//****************************************
//****************************************

//二维地图
template<typename T>
class GameMap {
	friend class GameFunction;
private:
	std::vector<std::vector<T>> Map;
	int width;
	int height;

	explicit GameMap();
public:
	GameMap(const int width, const int height);
	GameMap(const GameMap& Map2);
	GameMap(GameMap&& Map2);
	const GameMap<T>& operator=(const GameMap<T>& Map2);
	
	const int getWidth()const;
	const int getHeight()const;

	const std::vector<std::vector<T>> getMap()const;
	const T& getPoint(const int x, const int y)const;
	const T& getPoint(const Point pos)const;

	const GameMap<T>& setWidth(const int Width);
	const GameMap<T>& setHeight(const int Height);

	const GameMap<T>& setMap(const GameMap<T>& Map2);
	const GameMap<T>& setPoint(const int x, const int y, const T& Data2);
	const GameMap<T>& setPoint(Point pos, const T& Data2);
};

template<typename T>
GameMap<T>::GameMap(const int Width, const int Height)
	:Map(std::vector<std::vector<T>>(Width, std::vector<T>(Height))), width(Width), height(Height)
{
}

template<typename T>
GameMap<T>::GameMap(const GameMap& Map2)
	: Map(std::vector<std::vector<T>>(Map2.width, std::vector<T>(Map2.height))), width(Map2.width), height(Map2.height)
{
}

template<typename T>
GameMap<T>::GameMap(GameMap&& Map2)
	: Map(std::vector<std::vector<T>>(Map2.width, std::vector<T>(Map2.height))), width(Map2.width), height(Map2.height)
{
	Map2.~Map();
}

template<typename T>
const GameMap<T>& GameMap<T>::operator=(const GameMap<T>& Map2)
{
	Map = Map2.Map;
	width = Map2.width;
	height = Map2.height;
	return*this;
}

template<typename T>
inline const int GameMap<T>::getWidth() const
{
	return width;
}

template<typename T>
inline const int GameMap<T>::getHeight() const
{
	return height;
}

template<typename T>
const std::vector<std::vector<T>> GameMap<T>::getMap() const
{
	return Map;
}

template<typename T>
const T& GameMap<T>::getPoint(const int x, const int y) const
{
	return Map[x][y];
}

template<typename T>
const T& GameMap<T>::getPoint(const Point pos) const
{
	int x = pos.getX() < width ? pos.getX() : width - 1;
	int y = pos.getY() < height ? pos.getY() : height - 1;
	return Map[x][y];
}

template<typename T>
inline const GameMap<T>& GameMap<T>::setWidth(const int Width)
{
	width = Width;
	return*this;
}

template<typename T>
inline const GameMap<T>& GameMap<T>::setHeight(const int Height)
{
	height = Height;
	return*this;
}

template<typename T>
const GameMap<T>& GameMap<T>::setMap(const GameMap<T>& Map2)
{
	this->Map = Map2.Map;
	width = Map2.width;
	height = Map2.height;
	return*this;
}

template<typename T>
const GameMap<T>& GameMap<T>::setPoint(const int x, const int y, const T& Data2)
{
	Map[x][y] = Data2;
	return*this;
}

template<typename T>
const GameMap<T>& GameMap<T>::setPoint(Point pos, const T& Data2)
{
	Map[pos.getX()][pos.getY()] = Data2;
	return*this;
}

//****************************************
//****************************************