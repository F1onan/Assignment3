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

	//Creates the board
	createBoard(board);

	//Add the players to the game and adjust the value of numofplayers
	assignPlayers(&numofplayers);


	for(i=0; i<numofplayers; i++)//Cycle through each player
	{
		abilities(numofplayers, i);

		//Assign player with a random row
		players[i].row = rand() % 7;
		players[i].column = rand() % 7;

		board[players[i].row][players[i].column].capacity++;//Set the boolean value, full, for the slot occupied by player #i to be true

		players[i].order=board[players[i].row][players[i].column].capacity-1;//The players position in playersHere
		board[players[i].row][players[i].column].playersHere[board[players[i].row][players[i].column].capacity-1]=i+1;//Assign the appropriate slot with the current player


		printf("Slot = (%d,%d)\n\n", players[i].row, players[i].column);//Print the player's slot
	}

	int numLeft = numofplayers;//Number of players remaining
	int round = 1;

	 while(numLeft > 1)
	 {
		printf("\n***************[ROUND %d]***************", round);

		for(i=0; i<numofplayers; i++)
		{
			if(players[i].dead==false)//If the player is still alive
			{
				printBoard(board);
				printf("%d players remain!\n\n", numLeft);
		    	move(numofplayers, i, players[i].row, players[i].column, board, &numLeft);
		    	if(players[i].life<0)
		    		players[i].dead=true;
			}
		}
		round++;//Go to the next round
	 }

	 //Search for the one remaining player who isn't dead
	 for(i=0; i<numofplayers; i++)
	 {
		 if(players[i].dead == false)
			 printf("\n\nPlayer #%d (%s) won the game with %.0f health remaining!", i+1, players[i].name, players[i].life);
	 }


  return 0;
}
