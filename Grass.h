#pragma once
#include <string>
#include <vector>
#include "Game.h"

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
	const bool operator==(const Grass& grass)const;
	const bool operator!=(const Grass& grass)const;

	// get
	Point getPosition()const;
	const int getCount()const;
	const std::string getGrassPic()const;

	void Draw()const;
};

//��ƺ
class Lawn :public GameMap<Grass> {
private:
	std::vector<Grass> grassList;

	Lawn& This = *this;

	void set0Position();

public:
	Lawn(const int width, const int height);
	Lawn(const int width, const int height, const std::vector<Grass> GrassList);
	Lawn(const int width, const int height, const int grassCount);
	Lawn(const Lawn& lawn2);
	Lawn(Lawn&& lawn2);
	const Lawn& operator=(const Lawn& lawn2);
	const bool operator==(const Lawn& lawn2)const;
	const bool operator!=(const Lawn& lawn2)const;

	const std::vector<Grass>& getGrassList()const;

	// ���ظ�Point�ز���Count��Grass����
	const Lawn& makeGrass(int grassCount);

	// ����һ��Grass�����и�����
	const Lawn& plantGrass(Grass& grass);

	// ��Point����Grass
	const Lawn& unmakeGrass(Point pos);

	// ������ȫһ����Grass
	const Lawn& unmakeGrass(Grass& grass);

	// ����������ƺ
	const Lawn& Draw()const;
};