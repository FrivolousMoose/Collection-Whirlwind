#include "Entity.h"
#include "Animations.h"
#include "Renderer2D.h"



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

		//mercyFrames += deltaTime;
		//m_opacity = (cos(mercyFrames * 10) + 2) / 2;
	}
}

void::Entity::draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(1, 1, 1, m_opacity);
	m_animation->draw(renderer, m_position.x, m_position.y);
}