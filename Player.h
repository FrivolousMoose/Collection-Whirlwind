#include "Entity.h"

#pragma once
class Player : public Entity
{
public:
	Player();
	~Player();

	unsigned char getHealth() { return m_health; }
	int getScore() { return m_score; }
	int getForm() { return m_form; }

	void addScore(int points) { m_score += points; }

	void switchForm();
	void takeDamage();
	void reset();


	void update(float deltaTime);

private:
	int m_health;
	int m_score;

	float m_mercyTime;
	
};

