/*
 * main.c
 *
 *  Created on: 31 Mar 2017
 *      Author: College
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int main(void)
{
	int i;
	int numofplayers;
	setbuf(stdout, NULL);//Allows scanf to function properly
	srand(time(NULL));//Seed the random number generator

	//The board is represented as a pointer of pointer to slots
	//This allocates in memory the space for the pointers to each row of the board
	struct slot ** board = malloc(7 * sizeof(struct slot *));

	//pointer to slot (0,0)
	struct slot *upLeft;

	//pointer to slot (0,boardSize -1)
	struct slot *upRight;

	//pointer to slot (boardSize - 1, 0)
	struct slot *downLeft;

	//pointer to slot (boardSize - 1, boardSize -1)
	struct slot *downRight;

	//Creates the board
	createBoard(board, &upLeft, &upRight, &downLeft, &downRight);

	//Add the players to the game and adjust the value of numofplayers
	assignPlayers(&numofplayers);


	for(i=0; i<numofplayers; i++)//Cycle through each player
	{
		abilities(numofplayers, i);

		//Assign player with a random row
		players[i].row = rand() % 7;
		players[i].column = rand() % 7;

		board[players[i].row][players[i].column].capacity++;//Set the boolean value, full, for the slot occupied by player #i to be true

		players[i].order=board[players[i].row][players[i].column].capacity;//The players position in playersHere
		board[players[i].row][players[i].column].playersHere[board[players[i].row][players[i].column].capacity-1]=i;//Assign the appropriate slot with the current player


		printf("Slot = (%d,%d)\n\n", players[i].row, players[i].column);

		/*If the the required slot is closer to the down-right
		 * corner of the board the search starts from downRight,
		 * which points to slot at position (boardSize-1, boarSize -1)*/
		if(players[i].row >= 3){
			if(players[i].column >= 3)
				reachDesiredElement(players[i].row,players[i].column,downRight);
			else
			/*If the the required slot is closer to the down-left
			* corner of the board the search starts from downLeft,
			* which points to slot at position (boardSize-1, 0)*/
				reachDesiredElement(players[i].row,players[i].column,downLeft);
		} else {
			/*If the the required slot is closer to the up-right
			* corner of the board the search starts from upRight,
			* which points to slot at position (0, boarSize -1)*/
			if(players[i].column >= 3)
				reachDesiredElement(players[i].row,players[i].column, upRight);
			/*If the the required slot is closer to the up-left
			* corner of the board the search starts from upLeft,
			* which points to slot at position (0, 0)*/
			else reachDesiredElement(players[i].row,players[i].column,upLeft);
		}
	}

	int numLeft = numofplayers;//Number of players remaining
	int round = 1;

	 while(numLeft > 1)
	 {
		printf("\n***************[ROUND %d]***************", round);

		for(i=0; i<numofplayers; i++)
		{
			printBoard(board);
			move(numofplayers, i, players[i].row, players[i].column, board, &numLeft);
		}
		printf("THERE ARE %d PLAYERS LEFT", numLeft);
		round++;
	 }


		return 0;
}
