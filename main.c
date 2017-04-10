/*
 * main.c
 *
 *  Created on: 31 Mar 2017
 *      Author: College
 */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void)
{
	int row, column, i;
	int numofplayers;
	setbuf(stdout, NULL);

		//pointer to slot (0,0)
		struct slot *upLeft;

		//pointer to slot (0,boardSize -1)
		struct slot *upRight;

		//pointer to slot (boardSize - 1, 0)
		struct slot *downLeft;

		//pointer to slot (boardSize - 1, boardSize -1)
		struct slot *downRight;

		//Creates the board
		createBoard(7 ,&upLeft, &upRight, &downLeft, &downRight);

		assignPlayers(&numofplayers);


		for(i=0; i<numofplayers; i++)//Cycle through each player
		{
		abilities(numofplayers, i);

		/*	Asks the user the row and the column of the slot
			s/he wants to go to on the board.         */
		getDesiredElement(&row,&column, i);
		}
		//Finds the slot


		/*If the the required slot is closer to the down-right
		 * corner of the board the search starts from downRight,
		 * which points to slot at position (boardSize-1, boarSize -1)*/
		if(row >= 7/2){
			if(column >= 7/2)
				reachDesiredElement(row,column,downRight);
			else
			/*If the the required slot is closer to the down-left
			* corner of the board the search starts from downLeft,
			* which points to slot at position (boardSize-1, 0)*/
				reachDesiredElement(row,column,downLeft);
		} else {
			/*If the the required slot is closer to the up-right
			* corner of the board the search starts from upRight,
			* which points to slot at position (0, boarSize -1)*/
			if(column >= 7/2)
				reachDesiredElement(row,column, upRight);
			/*If the the required slot is closer to the up-left
			* corner of the board the search starts from upLeft,
			* which points to slot at position (0, 0)*/
			else reachDesiredElement(row,column,upLeft);
		}

		return 0;
}
