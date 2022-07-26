#include <iostream>
#include <limits.h>

#if _WIN32
#include <Windows.h>
#include <time.h>
#else
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#endif

/*
 * Console tiny game.
 * Tic-tac-toe.
 */

static short posValueArr[9];

static short lastPos = -1;

static int genRand() {
#if _WIN32
	return rand();
#else
	return rand();
#endif
}

static void sysInitRand() {
#if _WIN32
	srand((unsigned int)time(NULL));
#else
	srand((unsigned int)time(NULL));
#endif
}

static void sysSetTitle(const char* const title) {
#if _WIN32
	std::string cmd("title ");
	cmd.append(title);
	system(cmd.c_str());
#else
	// TODO: implement
#endif
}

static void sysClear() {
#if _WIN32
	system("cls");
#else
	system("clear")
#endif
}

enum class GameResult {
	HUMAN,
	BOT,
	DRAW,
	NONE
};

/*
* Update playing field.
*/
static void updatePlayingField() {

	sysClear();

	if (posValueArr[0] == -1)
		std::cout << "_|";
	else if (posValueArr[0] == 0)
		std::cout << "0|";
	else
		std::cout << "X|";

	if (posValueArr[1] == -1)
		std::cout << "_";
	else if (posValueArr[1] == 0)
		std::cout << "0";
	else
		std::cout << "X";

	if (posValueArr[2] == -1)
		std::cout << "|_";
	else if (posValueArr[2] == 0)
		std::cout << "|0";
	else
		std::cout << "|X";

	std::cout << std::endl;

	if (posValueArr[3] == -1)
		std::cout << "_|";
	else if (posValueArr[3] == 0)
		std::cout << "0|";
	else
		std::cout << "X|";

	if (posValueArr[4] == -1)
		std::cout << "_";
	else if (posValueArr[4] == 0)
		std::cout << "0";
	else
		std::cout << "X";

	if (posValueArr[5] == -1)
		std::cout << "|_";
	else if (posValueArr[5] == 0)
		std::cout << "|0";
	else
		std::cout << "|X";

	std::cout << std::endl;

	if (posValueArr[6] == -1)
		std::cout << " |";
	else if (posValueArr[6] == 0)
		std::cout << "0|";
	else
		std::cout << "X|";

	if (posValueArr[7] == -1)
		std::cout << " ";
	else if (posValueArr[7] == 0)
		std::cout << "0";
	else
		std::cout << "X";

	if (posValueArr[8] == -1)
		std::cout << "| ";
	else if (posValueArr[8] == 0)
		std::cout << "|0";
	else
		std::cout << "|X";

	std::cout << std::endl;

}

/*
* Set 0 to a specific position if possible.
*/
static bool setPos0(unsigned short pos) {
	if (posValueArr[pos] == -1) {
		posValueArr[pos] = 0;
		return true;
	}
	return false;
}

/*
* Set X to a specific position if possible.
*/
static bool setPosX(unsigned short pos) {
	if (posValueArr[pos] == -1) {
		lastPos = pos;
		posValueArr[pos] = 1;
		return true;
	}
	return false;
}

/*
* Bot is playing.
*/
static void botPlay() {

	for (unsigned int value = 0; value < 2; ++value) {

		unsigned short pos = 0;

		for (unsigned int i = 0; i < 8; ++i) {

			// two in a row horizontally
			if (i != 2 && i != 5 && posValueArr[i] == value && posValueArr[i + 1] == value) {

				pos = i + 1 + 1;
				if (pos % 3 == 0)
					pos = i - 1;

				if (setPos0(pos))
					return;
			}

			// two in a row vertically
			if (i <= 5 && posValueArr[i] == value && posValueArr[i + 3] == value) {

				pos = i + 3 + 3;
				if (pos > 8)
					pos = i - 3;

				if (setPos0(pos))
					return;
			}

			// two through one cell horizontally
			if (i <= 6 && i != 2 && i != 5 && posValueArr[i] == value && posValueArr[i + 2] == value) {
				pos = i + 1;
				if (setPos0(pos))
					return;
			}

			// two through one cell vertically
			if (i <= 2 && posValueArr[i] == value && posValueArr[i + 6] == value) {
				pos = i + 6 - 3;
				if (setPos0(pos))
					return;
			}

		}

		// two in a row diagonally
		if (posValueArr[4] == value && (
			posValueArr[0] == value
			|| posValueArr[2] == value
			|| posValueArr[6] == value
			|| posValueArr[8] == value)
			)
		{
			if (posValueArr[0] == value)
				pos = 8;
			else if (posValueArr[8] == value)
				pos = 0;
			else if (posValueArr[2] == value)
				pos = 6;
			else if (posValueArr[6] == value)
				pos = 2;

			if (setPos0(pos))
				return;
		}

		// two diagonally across the cage
		if ((posValueArr[0] == value && posValueArr[8] == value) || (posValueArr[2] == value && posValueArr[6] == value))
			setPos0(4);
	}

	// Set to random position
	unsigned short rndPos = (unsigned short)(genRand() % 8 + 1);
	if (rndPos == lastPos)
	{
		if (lastPos == 8)
			--rndPos;
		else
			++rndPos;
	}

	setPos0(rndPos);

}

/*
* Calculates the winner.
*/
static GameResult check() {

	if ((posValueArr[0] == 1 && posValueArr[1] == 1 && posValueArr[2] == 1)
		|| (posValueArr[3] == 1 && posValueArr[4] == 1 && posValueArr[5] == 1)
		|| (posValueArr[6] == 1 && posValueArr[7] == 1 && posValueArr[8] == 1)
		|| (posValueArr[0] == 1 && posValueArr[3] == 1 && posValueArr[6] == 1)
		|| (posValueArr[1] == 1 && posValueArr[4] == 1 && posValueArr[7] == 1)
		|| (posValueArr[2] == 1 && posValueArr[5] == 1 && posValueArr[8] == 1)
		|| (posValueArr[0] == 1 && posValueArr[4] == 1 && posValueArr[8] == 1)
		|| (posValueArr[2] == 1 && posValueArr[4] == 1 && posValueArr[6] == 1)
		)
		return GameResult::HUMAN;

	if ((posValueArr[0] == 0 && posValueArr[1] == 0 && posValueArr[2] == 0)
		|| (posValueArr[3] == 0 && posValueArr[4] == 0 && posValueArr[5] == 0)
		|| (posValueArr[6] == 0 && posValueArr[7] == 0 && posValueArr[8] == 0)
		|| (posValueArr[0] == 0 && posValueArr[3] == 0 && posValueArr[6] == 0)
		|| (posValueArr[1] == 0 && posValueArr[4] == 0 && posValueArr[7] == 0)
		|| (posValueArr[2] == 0 && posValueArr[5] == 0 && posValueArr[8] == 0)
		|| (posValueArr[0] == 0 && posValueArr[4] == 0 && posValueArr[8] == 0)
		|| (posValueArr[2] == 0 && posValueArr[4] == 0 && posValueArr[6] == 0)
		)
		return GameResult::BOT;

	for (const auto value : posValueArr) {
		if (value == -1)
			return GameResult::NONE;
	}

	return GameResult::DRAW;
}

/*
* Displays information about the winner of the game.
*/
static void displayWin(const GameResult result) {

	switch (result)
	{
	case GameResult::BOT:
		std::cout << std::endl << "Bot win!" << std::endl << std::endl;
		break;
	case GameResult::HUMAN:
		std::cout << std::endl << "Human win!" << std::endl << std::endl;
		break;
	case GameResult::DRAW:
		std::cout << std::endl << "DRAW!" << std::endl << std::endl;
		break;
	default:
		throw std::runtime_error("invalid result");
	}
}

/*
* Starts the game.
*/
void gameStart() {

	sysInitRand();

	updatePlayingField();

	while (true) {
		std::cout << std::endl << "Enter position" << std::endl << std::endl;

		unsigned short pos = 0;

		// Validation input
		if (!(std::cin >> pos) || pos == 0 || pos > 9) {
			std::cin.clear();
			std::cin.ignore(LLONG_MAX, '\n');
			std::cerr << "Invalid input" << std::endl;
			continue;
		}

		// Set X to input position
		if (!setPosX(pos - 1)) {
			std::cerr << "Position occupied" << std::endl << std::endl;
			continue;
		}

		updatePlayingField();
		GameResult gameResult = check();
		if (gameResult != GameResult::NONE) {
			displayWin(gameResult);
			break;
		}

		botPlay();
		Sleep(500);

		updatePlayingField();
		gameResult = check();
		if (gameResult != GameResult::NONE) {
			displayWin(gameResult);
			break;
		}
	}
}

/*
* Displays info about current application and show position numbers.
*/
void displayInfo() {

	std::cout << "***************************" << std::endl;
	std::cout << "***** tic-tac-toe bot *****" << std::endl;
	std::cout << "***************************" << std::endl << std::endl;

	std::cout << "You - X, bot - 0. Position numbers:" << std::endl;
	std::cout << "1|2|3" << std::endl;
	std::cout << "4|5|6" << std::endl;
	std::cout << "7|8|9" << std::endl << std::endl;
}

int main()
{
	sysSetTitle("tic-tac-toe");

	displayInfo();

	while (true) {

		// -1 this is an unset value
		memset(posValueArr, -1, sizeof(posValueArr));

		// Dialog
		std::cout << "Start game(Y/N)?" << std::endl;
		try {
			char answer;
			if (!(std::cin >> answer))
				throw std::invalid_argument("Invalud input");

			if (answer == 'Y' || answer == 'y')
				gameStart();
			else if (answer == 'N' || answer == 'n')
				return 0;
			else
				throw std::invalid_argument("Invalud input");
		}
		catch (const std::invalid_argument& ex) {
			std::cerr << ex.what() << std::endl;
			return 1;
		}
	}

}