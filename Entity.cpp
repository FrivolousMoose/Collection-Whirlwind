#include "Entity.h"
#include "Animations.h"
#include "Renderer2D.h"
#include "Defines.h"



Entity::Entity()
{
	m_isAlive = true;
	m_opacity = 1;
}


Entity::~Entity()
{
	if (m_animation != nullptr)
	{
		delete m_animation;
	}
}

void Entity::setAnimation(const char* animFilename, unsigned int frames, unsigned int columns, glm::vec2 size)
{
	m_animation = new Animations(animFilename, frames, columns, size);
	//m_size = m_animation->getFrameSize();
}

void::Entity::update(float deltaTime)
{
	if (m_isAlive == true)
	{
		m_position += m_velocity * deltaTime;
	}
}

void::Entity::draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(1, 1, 1, m_opacity);
	m_animation->draw(renderer, m_position.x, m_position.y);
	renderer->setRenderColour(1, 1, 1, 1);
}

bool Entity::collision(Entity* entity)
{
	return (m_position.x < entity->m_position.x + entity->m_size.x) &&		
		(m_position.x + m_size.x > entity->m_position.x) &&
		(m_position.y - m_size.y < entity->m_position.y) &&
		(m_position.y > entity->m_position.y - entity->m_size.y);
}

bool Entity::hasAdvantage(Entity* entity)
{
	return (m_form == SCISSORS && entity->m_form == PAPER) ||
		(m_form == PAPER && entity->m_form == ROCK) ||
		(m_form == ROCK && entity->m_form == SCISSORS);
}