#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game
{
public:
	int state;
	//game = 1
	//win = 2
	//lose = 3
	unsigned int widthGame, heightGame;

	Game(unsigned int width = 800, unsigned int height = 600);
	~Game();
	void input(float in);
	void update(float in);
	void render();
};

#endif