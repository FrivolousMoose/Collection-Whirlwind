#include "Entity.h"


class Collectable : public Entity
{
public:
	Collectable();
	Collectable(int xPos, int velocity, int form);
	~Collectable();

	void update(float deltaTime);
	void reset(int xPos, int velocity, int form, bool isAlive);
};
