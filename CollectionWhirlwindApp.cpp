#include "CollectionWhirlwindApp.h"
#include "Player.h"
#include "Collectable.h"
#include <Texture.h>
#include <Input.h>
#include <stdlib.h>
#include <time.h>
#include "ObjectPool.h"


CollectionWhirlwindApp::CollectionWhirlwindApp()
{
}


CollectionWhirlwindApp::~CollectionWhirlwindApp()
{
}


bool CollectionWhirlwindApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();

	pool = new ObjectPool<Collectable>(20);


	time = 0;
	return true;

}

void CollectionWhirlwindApp::shutdown()
{
}

void CollectionWhirlwindApp::updateGame(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	time += deltaTime;

	if (time > 1)
	{
		if (pool->ReturnItems() < 15)
		{

			auto object = pool->AllocateObject();
			object->reset( (rand() % 910) + 25, (rand() % 50) + 50,rand() % 3);
			m_collectables.push_back(object);
		}
		time = 0;
	}


	for (int i = 0; i < pool->ReturnItems(); )
	{

		if ((m_collectables[i])->isAlive() == false)
		{
			pool->DeallocateObject(m_collectables[i]);
			m_collectables.erase(m_collectables.begin() + pool->ReturnItems());
		}
		else
		{
			(m_collectables[i])->update(deltaTime);
			i++;
		}
	}


	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		quit();
	}

}

void CollectionWhirlwindApp::update(float deltaTime)
{
	updateGame(deltaTime);
}

void CollectionWhirlwindApp::draw()
{
	clearScreen();

	m_2dRenderer->begin();
	for (int i = 0; i < pool->ReturnItems(); )
	{
		(m_collectables[i])->draw(m_2dRenderer);
		i++;
	}
	m_2dRenderer->end();
}