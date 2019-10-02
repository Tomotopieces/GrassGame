#pragma once
#include <string>
#include <vector>
#include "Game.h"

const std::vector<std::string> GrassPic1 = { "/", "\\", "`", "~", "-", "^" };
const std::vector<std::string> GrassPic2 = { "v", "V", "y", "Y", ">", "#" };

//��
class Grass {
private:
	//�ݵ�λ��
	Point point;
	//�ݵ�����
	int count;
	//�ݵ�����
	std::string grassPic;

	void setPic();

public:
	// ����ص����������
	Grass();

	Grass(const Grass& grass2);
	Grass(Grass&& grass2);

	// �������
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

	// ���ظ�Point�ز���Count��Grass����
	const Lawn& makeGrass(int grassCount);

	// ����һ��Grass�����и�����
	const Lawn& plantGrass(Grass& grass);

	// ��Point����Grass
	const Lawn& unmakeGrass(Point pos);

	// ������ȫһ����Grass��allΪfalseʱֻ����һ��
	const Lawn& unmakeGrass(Grass& grass, bool all = true);

	const Lawn& Draw()const;
};