#include <glm/vec2.hpp>

namespace aie {
	class Renderer2D;
	class Texture;
};

class Animations
{
	Animations();
public:
	Animations(const char* filename, unsigned int frames, unsigned int columns, glm::vec2 size);
	~Animations();

	glm::vec2 getFrameSize();

	void setCurrentFrame(int frame) { m_current = frame; }

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer, int x, int y);

private:
	unsigned int m_frames;
	unsigned int m_current;
	float m_time;

	int m_columns;

	aie::Texture* m_texture;
	glm::vec2 m_size;
};

