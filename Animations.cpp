#include "Animations.h"
#include <Renderer2D.h>
#include <Texture.h>
#include <memory>
#include <iostream>


Animations::Animations()
{
	m_frames = 0;
	m_current = 0;
	m_time = 0.0f;
	int m_columns = 1;
}

Animations::Animations(const char* filename, unsigned int frames, unsigned int columns, glm::vec2 size)
{
	m_texture = new aie::Texture(filename);
	m_frames = frames;
	m_current = 0;
	m_columns = columns;
	m_size = size;
}


Animations::~Animations()
{
	if (m_texture != nullptr)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}

glm::vec2 Animations::getFrameSize()
{
	float percent = 1.0f / ((float)m_frames + 1.0f);
	float width = m_texture->getWidth() * percent;
	float height = m_texture->getHeight();
	return glm::vec2(width, height);
}

void Animations::update(float deltaTime)
{
	m_time += deltaTime;

	if (m_time > 0.25)
	{
		m_time -= 0.25;
		m_current++;

		if (m_current >= m_frames)
		{
			m_current = 0;
		}

	}
}

void Animations::draw(aie::Renderer2D* renderer, int x, int y)
{
	//Finds the total number of rows, in the case that there are blank frames at the end of the sprite sheet
	int rows = ceil((float)m_frames / (float)m_columns);

	//Finds horizontal and vertical starting pixels, respectively. Should work with sprites that have only one row.
	int column = (int)m_current % (int)m_columns;
	int row = (int)m_current / (int)m_columns;

	//Finds width and height of the current frame
	int width = m_texture->getWidth() / m_columns;
	int height = m_texture->getHeight() / rows;

	renderer->setUVRect((float)column / (float)m_columns, (float)row / (float)rows, 1.0f / (float)m_columns, 1.0f / (float)rows);
	renderer->drawSprite(m_texture, x, y, m_size.x, m_size.y) ;
	renderer->setUVRect(0, 0, 1, 1);
}
