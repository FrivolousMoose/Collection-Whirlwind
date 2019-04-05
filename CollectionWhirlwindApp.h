#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <list>
#include <vector>
#include "Defines.h"


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

	void reset();

	void updateGame(float deltaTime);
	void updateMenu();
	void updatePause();
	void updateHowTo();
	void updateGameOver();

	void drawGame();
	void drawMenu();
	void drawPause();
	void drawHowTo();
	void drawGameOver();

	virtual void update(float deltaTime);
	virtual void draw();

private:
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	aie::Font* m_fontBold;

	float m_spawnTime;
	float m_formTime;
	int m_state = MENU;

	int m_menuSelection = 0;

	ObjectPool<Collectable>* pool;
	std::vector<Collectable*> m_collectables;
	Player* m_player;


};

