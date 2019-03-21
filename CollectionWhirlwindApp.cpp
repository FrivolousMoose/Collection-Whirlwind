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
	delete m_2dRenderer;
	m_collectables.clear();
	delete pool;
	//for (std::vector<Collectable*>::iterator iter = m_collectables.begin(); iter != m_collectables.end(); iter++)
	//	{
	//		delete (*iter);
	//	}
	delete m_player;

}


bool CollectionWhirlwindApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();

	pool = new ObjectPool<Collectable>(20);
	m_player = new Player();


	spawnTime = 0;
	return true;

}

void CollectionWhirlwindApp::shutdown()
{
}

void CollectionWhirlwindApp::updateGame(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	spawnTime += deltaTime;

	//Spawns an enemy every second, unless enemy count is maxed out.
	if (spawnTime > 1)
	{
		if (pool->ReturnItems() < pool->ReturnSize())
		{

			auto object = pool->AllocateObject();
			object->reset( (rand() % 910) + 25, (rand() % 50) + 50,rand() % 3, true);
			m_collectables.push_back(object);
		}
		spawnTime = 0;
	}

	m_player->update(deltaTime);

	for (int i = 0; i < pool->ReturnItems(); )
	{

		if ((m_collectables[i])->isAlive() == false)
		{
			//Replaces the data of the dead collectable with that of the last active one, then deletes the last active collectable.
			pool->DeallocateObject(m_collectables[i]);
			m_collectables.erase(m_collectables.begin() + pool->ReturnItems());
		}
		else
		{
			(m_collectables[i])->update(deltaTime);
			i++;
		}
	}

	for (int i = 0; i < pool->ReturnItems(); )
	{
		if (m_player->collision(m_collectables[i]))
		{
			//Gives a lot of points if player has the advantage
			if (m_player->hasAdvantage(m_collectables[i]))
			{
				m_collectables[i]->setDead();
			}
			//Hurts the player if the enemy has an advantage
			else if (m_collectables[i]->hasAdvantage(m_player))
			{
				m_player->takeDamage();
			}
			//Gives the player a few points if they're the same
			else
			{

			}
			m_collectables[i]->setDead();

		}
		i++;
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
	m_player->draw(m_2dRenderer);
	m_2dRenderer->end();
}