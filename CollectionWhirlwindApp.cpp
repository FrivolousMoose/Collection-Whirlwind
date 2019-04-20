#include "CollectionWhirlwindApp.h"
#include "Player.h"
#include "Collectable.h"
#include "Font.h"
#include "ObjectPool.h"
#include <Texture.h>
#include <Input.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

CollectionWhirlwindApp::CollectionWhirlwindApp()
{
}


CollectionWhirlwindApp::~CollectionWhirlwindApp()
{
	delete m_2dRenderer;
	delete m_font;
	delete m_fontBold;

	delete pool;
	delete m_player;

}


bool CollectionWhirlwindApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/Consolas.ttf", 18);
	m_fontBold = new aie::Font("./font/Consolas_bold.ttf", 18);

	const int poolSize = 20;
	pool = new ObjectPool<Collectable>(poolSize);

	m_player = new Player();

	m_spawnTime = 0;
	m_spawnRate = 2;
	m_formTime = FORM_LENGTH;
	return true;

}

void CollectionWhirlwindApp::shutdown()
{
}

void CollectionWhirlwindApp::reset()
{
	m_player->reset();

	m_spawnTime = 0;
	m_spawnRate = 2;
	m_formTime = FORM_LENGTH;

	for (int i = 0; i < pool->ReturnItems(); )
	{
		pool->DeallocateObject(m_collectables[i]);
		m_collectables.erase(m_collectables.begin() + pool->ReturnItems());
	}
}

void CollectionWhirlwindApp::updateGame(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	m_spawnTime += deltaTime;
	m_formTime -= deltaTime;

	m_collectables.begin();

	//Spawns an enemy every second, unless enemy count is maxed out.
	if (m_spawnTime > m_spawnRate)
	{
		if (pool->ReturnItems() < pool->ReturnSize())
		{

			auto object = pool->AllocateObject();
			object->reset( (rand() % 910) + 25, (rand() % 50) + 50,rand() % 3, true);
			m_collectables.push_back(object);
		}
		m_spawnTime = 0;
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
			//Gives a lot of points if player has the advantage, increasing with how long they've been playing
			if (m_player->hasAdvantage(m_collectables[i]))
			{
				m_player->addScore(ceil(10 / m_spawnRate));
			}
			//Hurts the player if the enemy has an advantage
			else if (m_collectables[i]->hasAdvantage(m_player))
			{
				m_player->takeDamage();
			}
			//Gives the player a point if they're the same
			else
			{
				m_player->addScore(1);
			}
			m_collectables[i]->setDead();

		}
		i++;
	}

	//Switches the player's form every time the form timer hits 0
	if (m_formTime <= 0)
	{
		m_player->switchForm();
		m_formTime = FORM_LENGTH;
		m_spawnRate -= m_spawnRate > 0.6 ? 0.3 : 0;
	}

	//Changes the game state if the player is dead
	if (!m_player->isAlive())
	{
		m_state = GAME_OVER;
	}

	//Pauses the game When ESCAPE is PRESSED
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		m_state = PAUSE;
	}
}

void CollectionWhirlwindApp::updateMenu()
{
	aie::Input* input = aie::Input::getInstance();


	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		switch (m_menuSelection)
		{
			//Could possibly have just a single image with variables denoting the start frame and number of frames to go through?
		case 0:
			reset();
			m_state = GAME;
			break;
		case 1:
			m_state = HOWTO;
			break;
		case 2:
			quit();
			break;
		}
	}


	if (input->wasKeyPressed(aie::INPUT_KEY_UP) && m_menuSelection > 0)
	{
		m_menuSelection--;
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_DOWN) && m_menuSelection < 2)
	{
		m_menuSelection++;
	}
}

void CollectionWhirlwindApp::updatePause()
{
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		m_state = GAME;
	}


	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		m_state = MENU;
	}

}
void CollectionWhirlwindApp::updateHowTo()
{
	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE) || input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		m_state = MENU;
	}
}
void CollectionWhirlwindApp::updateGameOver()
{
	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE) || input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		m_state = MENU;
	}
}

void CollectionWhirlwindApp::drawGame()
{
	clearScreen();

	m_2dRenderer->begin();

	//m_2dRenderer->drawSprite(m_texture, x, y, m_size.x, m_size.y);
	//m_2dRenderer->setUVRect(0, 0, 1, 1);
	for (int i = 0; i < pool->ReturnItems(); )
	{
		(m_collectables[i])->draw(m_2dRenderer);
		i++;
	}
	m_player->draw(m_2dRenderer);

	//Drawing text
	char buffer[50];

	sprintf_s(buffer, "Health: %d", m_player->getHealth());
	m_2dRenderer->drawText(m_font, buffer, 32, 700);

	sprintf_s(buffer, "Score: %.4d", m_player->getScore());
	m_2dRenderer->drawText(m_font, buffer, 192, 700);

	int currentForm = m_player->getForm();
	const char* nextForm = currentForm == 0 ? "PAPER" : currentForm == 1 ? "ROCK" : currentForm == 2 ? "SCISSORS" : "ERROR";
	sprintf_s(buffer, "Next Form: %s", nextForm);
	m_2dRenderer->drawText(m_font, buffer, 732, 700);

	sprintf_s(buffer, "Next Form in: %.1f", m_formTime);
	m_2dRenderer->drawText(m_font, buffer, 502, 700);


	m_2dRenderer->end();
}

void CollectionWhirlwindApp::drawMenu()
{
	clearScreen();
	m_2dRenderer->begin();

	m_2dRenderer->drawText(m_fontBold, "OH NO, MY PRIZED COLLECTION OF STATIONARY AND MINERALS HAS BEEN SUCKED UP INTO A VORTEX", 50, 600);

	if (m_menuSelection == 0)
	{
		m_2dRenderer->drawText(m_fontBold , "Play", 440, 410);
	}
	else m_2dRenderer->drawText(m_font, "Play", 440, 410);
	if (m_menuSelection == 1)
	{
		m_2dRenderer->drawText(m_fontBold, "How To", 440, 370);
	}
	else m_2dRenderer->drawText(m_font, "How To", 440, 370);
	if (m_menuSelection == 2)
	{
		m_2dRenderer->drawText(m_fontBold, "Exit", 440, 330);
	}
	else m_2dRenderer->drawText(m_font, "Exit", 440, 330);
	m_2dRenderer->end();
}

void CollectionWhirlwindApp::drawPause()
{
	m_2dRenderer->begin();

	m_2dRenderer->drawText(m_fontBold, "Paused", 430, 450);
	m_2dRenderer->drawText(m_fontBold, "Press ESC to go to the menu and ENTER to resume game", 200, 400);

	m_2dRenderer->end();
}
void CollectionWhirlwindApp::drawHowTo()
{
	clearScreen();
	m_2dRenderer->begin();

	m_2dRenderer->drawText(m_fontBold, "Oh no, my prized collection of stationary and minerals has been caught up in a vortex!", 20, 650);
	m_2dRenderer->drawText(m_font, "I have surgically altered myself to periodically shift between scissors, paper and rock", 20, 610);
	m_2dRenderer->drawText(m_font, "I have also surgically modified myself to move with the ARROW KEYS", 20, 590);

	m_2dRenderer->drawText(m_font, "I need to be careful to pick up pieces of my collection when I'm in the right form,", 20, 550);
	m_2dRenderer->drawText(m_font, "otherwise I might damage my treasures, and that will hurt me. Emotionally", 20, 530);
	m_2dRenderer->drawText(m_font, "My anxiousness about the situation has caused me to switch forms every 20 seconds.", 20, 510);

	m_2dRenderer->drawText(m_font, "When I'm SCISSORS, I can safely pick up PAPER but will be hurt by ROCK", 20, 470);
	m_2dRenderer->drawText(m_font, "When I'm PAPER, I can safely pick up ROCK but will be hurt by SCISSORS", 20, 450);
	m_2dRenderer->drawText(m_font, "ROCK like SCISSOR. No like PAPER. ROCK kind of jerk.", 20, 430);


	m_2dRenderer->drawText(m_fontBold, "Good luck! Press ESCAPE or ENTER to go back to the menu", 100, 200);

	m_2dRenderer->end();
}
void CollectionWhirlwindApp::drawGameOver()
{
	clearScreen();
	m_2dRenderer->begin();

	m_2dRenderer->drawText(m_fontBold, "Game Over", 400, 450);

	char buffer[50];
	sprintf_s(buffer, "Final Score: %.4d", m_player->getScore());
	m_2dRenderer->drawText(m_font, buffer, 400, 400);
	m_2dRenderer->end();
}


void CollectionWhirlwindApp::update(float deltaTime)
{
	switch (m_state)
	{
	case MENU:
		updateMenu();
		break;
	case GAME:
		updateGame(deltaTime);
		break;
	case PAUSE:
		updatePause();
		break;
	case HOWTO:
		updateHowTo();
		break;
	case GAME_OVER:
		updateGameOver();
		break;
	}
}

void CollectionWhirlwindApp::draw()
{
	switch (m_state)
	{
	case MENU:
		drawMenu();
		break;
	case GAME:
		drawGame();
		break;
	case PAUSE:
		drawPause();
		break;
	case HOWTO:
		drawHowTo();
		break;
	case GAME_OVER:
		drawGameOver();
		break;
	}
}