#include "AiGame.h"
#include "Menu.h"

AiGame::AiGame()
{
	whiteTurn = 1;
	checkmate = 0;
	stalemate = 0;
	gameOver = 0;
	promotionChoice = 0;
	promotionTypeVec.push_back(QUEEN);
}

void AiGame::Init()
{
	while (window->isOpen())
	{
		UpdateEvents();
		Update();
		Print();
	}
}

void AiGame::Update()
{
	if (checkmate) {
		gameOver = 1;
		if (whiteTurn)
			text_msg.setString("Black won !");
		else
			text_msg.setString("White won !");
	}
	if (stalemate)
	{
		gameOver = 1;
		text_msg.setString("Stalemate !");
	}
	if (gamePaused)
	{
		for (auto btn : buttons)
			btn->HandleMouseHover(*window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (buttons[0]->IsMouseHover(*window)) {
				CleanBoard();
				gamePaused = false;
			}
			else if (buttons[1]->IsMouseHover(*window)) {
				gamePaused = false;
			}
			else if (buttons[2]->IsMouseHover(*window)) {
				window->close();
				Menu menu;
				menu.Start();
			}
		}
	}

	if (!gameOver && !gamePaused)
	{	
		if(whiteTurn)
			UpdateBoard();
		else
		{
			if (!promotionChoice) {
				AiMove();
				whiteTurn = !whiteTurn;
				HandleChecks();
				checkmateOrStalemate();
			}
			UpdateBoard();
		}
	}
	else
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttons[0]->IsMouseHover(*window))
			CleanBoard();
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		CleanBoard(); // restart the game.
	}

}

void AiGame::Print()
{
	window->clear();

	for (int i = 0; i < DIMENSIONS; i++)
	{
		for (int j = 0; j < DIMENSIONS; j++)
		{
			window->draw(squres[i * DIMENSIONS + j]);
		}
	}

	for (int i = 0; i < DIMENSIONS; i++)
	{
		for (int j = 0; j < DIMENSIONS; j++)
		{
			if (pieces[i][j])
			{
				pieces[i][j]->Print(window);
			}
		}
	}
	DrawNumbersLetters(window);
	for (auto circle : possibleCircles) {
		window->draw(circle);
	}
	
	if (gamePaused)
		for (auto btn : buttons)
			btn->DrawTo(*window);
	if (gameOver)
	{
		window->draw(text_msg);
		buttons[0]->DrawTo(*window);
		buttons[0]->HandleMouseHover(*window);
	}

	window->display();
}

bool AiGame::PlayerTurn(sf::Vector2i indexes)
{
	if (pieces[indexes.x][indexes.y]->IsWhite())
		return true;
	return false;
}
	
std::pair<sf::Vector2i, sf::Vector2i> AiGame::findBestMove()
{
	auto moves = AllLegalMoves(false);
	std::pair<sf::Vector2i, sf::Vector2i> bestMove;

	int randomIndex = rand() % moves.size();

	bestMove = moves[randomIndex];

	return bestMove;
}

void AiGame::AiMove()
{
	auto move = findBestMove();
	Move(move.first, move.second);
	std::string t = TranslateMove(move);
}