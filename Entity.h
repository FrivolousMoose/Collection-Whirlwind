#pragma once

#include <glm/vec2.hpp>

class Animations;

namespace aie {
	class Renderer2D;
	class Texture;
};

class Entity
{
public:
	Entity();
	~Entity();

	void setAnimation(const char* animFilename, unsigned int frames, unsigned int columns, glm::vec2 size);
	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);
	bool collision(Entity* entity);
	bool hasAdvantage(Entity* entity);
	void setDead() { m_isAlive = false; }

	bool isAlive() { return m_isAlive; }
	//bool getForm() { return m_form; }
protected:
	Animations * m_animation;

	bool m_isAlive;
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec2 m_velocity;
	int m_form;

	float m_opacity;
};

