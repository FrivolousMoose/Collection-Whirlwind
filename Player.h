#include "Entity.h"

#pragma once
class Player
{
public:
	Player();
	~Player();

	unsigned char gethealth() { return m_health; }
	int getScore() { return m_score; }


	void update();

private:
	unsigned char m_health;
	int m_score;

	int form;
	int m_mercyTime;
	
};

