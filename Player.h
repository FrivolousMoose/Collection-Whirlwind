#include "Entity.h"

#pragma once
class Player : public Entity
{
public:
	Player();
	~Player();

	unsigned char gethealth() { return m_health; }
	int getScore() { return m_score; }
	void switchForm(int form);
	void takeDamage();


	void update(float deltaTime);

private:
	int m_health;
	int m_score;

	float m_mercyTime;
	
};

