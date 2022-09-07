#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "AiGame.h"
#include "OfflineGame.h"
#include "Constants.h"

class Menu
{
public:
	Menu();
	void Start();
	void LoadData();
	void LoadSprites();
	void UpdateEvents();
	void Print();
	enum States { OFFLINE, AI};
private:
	sf::RenderWindow* window; 
	Game* game;
	std::vector<Button*> buttons;
	sf::Color btnColor;
	int limitFrom;
	int limitTo;
	sf::Texture chessBGTex;
	sf::Texture chessLogoTex;
	sf::Sprite chessBG;
	sf::Sprite chessLogo;
};