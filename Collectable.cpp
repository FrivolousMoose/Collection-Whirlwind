#include "Collectable.h"
#include "Defines.h"
#include "Animations.h"
#include <math.h>

Collectable::Collectable()
{
	m_form = 0;
	m_velocity = { 0, -50 };
	m_size = { 50, 50 };
	m_position = { 500, 720 + m_size.y / 2 };

	setAnimation("./textures/scissors.png", 7, 4, m_size);
}


Collectable::Collectable(int xPos, int velocity, int form)
{
	m_form = form;
	m_velocity = { 0, -velocity };
	m_size = { 50, 50 };
	m_position = { xPos, 720 + m_size.y/2 };

	switch (m_form)
	{
		//Could possibly have just a single image with variables denoting the start frame and number of frames to go through?
	case SCISSORS:
		setAnimation("./textures/scissors.png", 7, 4, m_size);
		break;
	case PAPER:
		setAnimation("./textures/paper.png", 3, 3, m_size);
		break;
	case ROCK:
		setAnimation("./textures/rock.png", 19, 5, m_size);
		break;
	}
}


Collectable::~Collectable()
{
}

void Collectable::reset(int xPos, int velocity, int form)
{
	m_form = form;
	m_velocity = { 0, -velocity };
	m_size = { 50, 50 };
	m_position = { xPos, 720 + m_size.y / 2 };

	switch (m_form)
	{
		//Could possibly have just a single image with variables denoting the start frame and number of frames to go through?
	case SCISSORS:
		setAnimation("./textures/scissors.png", 7, 4, m_size);
		break;
	case PAPER:
		setAnimation("./textures/paper.png", 3, 3, m_size);
		break;
	case ROCK:
		setAnimation("./textures/rock.png", 19, 5, m_size);
		break;
	}
}

void Collectable::update(float deltaTime)
{
	Entity::update(deltaTime);

	if (m_position.y < 0)
	{
		m_isAlive = false;
	}

	m_animation->update(deltaTime);
	
}