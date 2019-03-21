#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <list>
#include <vector>


template <typename T>
class ObjectPool;

class Collectable;
class Player;

class CollectionWhirlwindApp : public aie::Application
{
public:
	CollectionWhirlwindApp();
	virtual ~CollectionWhirlwindApp();

	virtual bool startup();
	virtual void shutdown();

	void updateGame(float deltaTime);

	virtual void update(float deltaTime);
	virtual void draw();

private:
	aie::Renderer2D* m_2dRenderer;
	float spawnTime;

	ObjectPool<Collectable>* pool;
	std::vector<Collectable*> m_collectables;
	Player* m_player;


};

