#pragma once
#include <string>
#include <vector>
#include "Game.h"

const std::vector<std::string> GrassPic1 = { "/", "\\", "`", "~", "-", "^" };
const std::vector<std::string> GrassPic2 = { "v", "V", "y", "Y", ">", "#" };

//草
class Grass {
private:
	//草的位置
	Point point;
	//草的数量
	int count;
	//草的样子
	std::string grassPic;

	void setPic();

public:
	// 随机地点和数量生草
	Grass();

	Grass(const Grass& grass2);
	Grass(Grass&& grass2);

	// 随机数量
	Grass(const Point pos);
	Grass(const int x, const int y);

	Grass(const Point pos, const int Count);
	Grass(const int x, const int y, const int Count);
	Grass& operator=(const Grass& grass2);

	Point getPosition()const;
	const int getCount()const;
	const std::string getGrassPic()const;

	const bool operator==(const Grass& grass)const;

	void Draw()const;
};

class Lawn :public GameMap<Grass> {
private:
	std::vector<Grass> grassList;

	void set0Position();

	explicit Lawn();
public:
	Lawn(int width, int height);
	Lawn(int width, int height, int grassCount);
	Lawn(Lawn& lawn2);
	Lawn(Lawn&& lawn2);
	const Lawn& operator=(const Lawn& lawn2);

	const std::vector<Grass>& getGrassList()const;

	// 不重复Point地产生Count个Grass对象
	const Lawn& makeGrass(int grassCount);

	// 储存一个Grass，具有覆盖性
	const Lawn& plantGrass(Grass& grass);

	// 按Point消除Grass
	const Lawn& unmakeGrass(Point pos);

	// 消除完全一样的Grass，all为false时只消除一个
	const Lawn& unmakeGrass(Grass& grass, bool all = true);

	const Lawn& Draw()const;
};