#include "Player.h"
#include "Input.h"
#include <math.h> 
#include "Animations.h"
#include "Defines.h"

Player::Player()
{
	m_form = 0;
	m_health = 3;
	m_velocity = { 0, 0 };
	m_size = { 50, 50 };
	m_position = { 480 + m_size.x / 2, 180 + m_size.y / 2 };
	setAnimation("./textures/scissors.png", 7, 4, m_size);
}


Player::~Player()
{
}

void Player::update(float deltaTime)
{
	Entity::update(deltaTime);

	aie::Input* input = aie::Input::getInstance();

	//Directional movement

	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		m_velocity.y += 2000 * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
			m_velocity.y -= 2000 * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
			m_velocity.x -= 2000 * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
			m_velocity.x += 2000 * deltaTime;
	}

	//Makes the player slow down by a factor of 20 every second. Serves the dual purpose of giving the player a smoother stop and limiting their functional max velocity.
	m_velocity *= pow(0.05, deltaTime);

	//Ensures the player completely stops moving after a while
	if ((m_velocity.x > -5 && m_velocity.x < 5) &&
		(m_velocity.y > -5 && m_velocity.y < 5))
	{
		m_velocity = {0,0};
	}
	
	//Teleports the player to the opposite end when they reach the horizontal boundary
	if (m_position.x > 960 + m_size.x/2)
	{
		m_position.x = 0 - m_size.x/2;
	}
	if (m_position.x < -m_size.x/2)
	{
		m_position.x = 960 + m_size.x/2;
	}

	//Prevents the player from leaving the vertical boundary of the screen
	if (m_position.y > 720 - m_size.y/2)
	{
		m_position.y = 720 - m_size.y/2;
		m_velocity.y = 0;
	}
	if (m_position.y < m_size.y/2)
	{
		m_position.y = m_size.y/2;
		m_velocity.y = 0;
	}

	if (m_mercyTime > 0)
	{
		m_mercyTime -= deltaTime;
		m_opacity = cos(m_mercyTime * 9) + 1;
	}
	else m_opacity = 1;
	

	if (m_health <= 0)
	{
		m_isAlive = false;
	}

	m_animation->update(deltaTime);
}

void Player::switchForm()
{
	//Testing this out. Still a little weird for me.
	m_form = 4;
	m_mercyTime = 3;

	switch (m_form)
	{
	case SCISSORS:
		setAnimation("./textures/scissors.png", 7, 4, m_size);
		break;
	case PAPER:
		setAnimation("./textures/paper.png", 3, 3, m_size);
		break;
	case ROCK:
		setAnimation("./textures/rock.png", 19, 5, m_size);
		break;
	default:
		assert(!"Invalid player form");
		break;
	}

}

void Player::reset()
{
	m_isAlive = true;
	m_mercyTime = 0;
	m_form = 0;
	m_health = 3;
	m_score = 0;
	m_velocity = { 0, 0 };
	m_size = { 80, 80 };
	m_position = { 480 + m_size.x / 2, 180 + m_size.y / 2 };
	setAnimation("./textures/scissors.png", 7, 4, m_size);
}

void Player::takeDamage()
{
	if (m_mercyTime <= 0)
	{
		m_health -= 1;
		m_mercyTime = 3;
	}
}

