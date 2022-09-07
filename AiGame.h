#pragma once
#include "Game.h"
#include <Windows.h>
#include <Wincrypt.h>
#include <inttypes.h>
#include <random>
#include <ctime>
#include <chrono>
#include <stdint.h>

class AiGame : public Game
{
public:
    // basic functions:
    AiGame();
    void Init(); // loop function.
    void Update();
    void Print(); // print all needed sprites to the screen.
    bool PlayerTurn(sf::Vector2i indexes);

    std::pair<sf::Vector2i, sf::Vector2i> findBestMove();
    void AiMove();

};