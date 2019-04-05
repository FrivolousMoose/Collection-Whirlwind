#pragma once

enum OBJECT_FORM
{
	SCISSORS,
	PAPER,
	ROCK,
};

enum GAME_STATE
{
	MENU,
	GAME,
	PAUSE,
	HOWTO,
	GAME_OVER,
};

const int MERCY_DELAY = 2;
const int FORM_LENGTH = 20;