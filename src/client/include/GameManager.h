

#ifndef REVERSI_GAMEMANAGER_H
#define REVERSI_GAMEMANAGER_H
#include "Board.h"
#include "NormalLogic.h"
#include "Player.h"
#include "Cell.h"
#include "Coordinate.h"
#include "Printer.h"
#include "Client.h"


class GameManager {
private:
    Board* board;
    Logic * logic;
    Player** players;
    Printer* printer;
    Client* client;
    int tie;
    bool isClientPlay;
    bool shouldStop;

public:
    /************************************************************************
	* Name: GameManager (Default Constructor)
	* Input: -
	* Output: -
	* Operation: Initialize the game and run it
	*************************************************************************/
    GameManager();

    /*************************************************************************
    * Name: GameManager (Constructor)
    * Input: size - the size of the board
    * Output: -
    * Operation: Initialize and manage a game with a spesific size of board
    *************************************************************************/
    GameManager(const int &size);

    /************************************************************************
   * Name: GameManager (Destructor)
   * Input: -
   * Output: -
   * Operation: Initialize the game and run it
   *************************************************************************/
    ~GameManager();

    /*************************************************************************
	* Name: Run
	* Input: -
	* Output: -
	* Operation: Run the game from start until someone win or there's a tie
	*************************************************************************/
    void run();

    /*************************************************************************
	* Name: PlayTurn
	* Input: player - The player who plays the current turn
	* Output: -
	* Operation: Plays a single turn. Checks possible moves and makes a move
	*************************************************************************/
    void playTurn(Player *&player);

    /*************************************************************************
	* Name: PutNext
	* Input: m - The manager of the moves,
    * player - The player who plays the current turn
	* Output: -
	* Operation: Puts the token where the player chose,
    * and flips all the appropriate tokens between them.
	*************************************************************************/
    void putNext(Player *&player, set<Coordinate> &availableMoves) const;

    /*************************************************************************
	* Name: Initialize
	* Input: size - The size of the board
	* Output: -
	* Operation: Set a new board in start mode
	*************************************************************************/
    void initialize(const int &size);

    /*************************************************************************
	* Name: EndGame
	* Input: -
	* Output: -
	* Operation: Finishes the game and frees all the allocations
	*************************************************************************/
    void endGame();

    /*************************************************************************
	* Name: Winner
	* Input: -
	* Output: -
	* Operation: Calculates and prints the winner (or tie)
	*************************************************************************/
    void winner() const;

    int clientCase();

    };


#endif //REVERSI_GAMEMANAGER_H
