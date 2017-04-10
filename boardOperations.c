/*
 * boardCreation.c

 *
 *  Created on: 29 Mar 2017
 *      Author: Fionan
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"



/*
 * This function creates the board
 * Parameters:
 * 	size: the size of the board
 * 	upLeft: pointer of pointer to slot at position (0, 0)
 * 	upRight: pointer of pointer to slot at position (0, 7 -1)
 * 	downLeft: pointer of pointer to slot at position (boardSsize -1, 0)
 * 	upLeft: pointer of pointer to slot at position (7 - 1, 7 -1)
 */
void createBoard(struct slot ** board, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight){

	srand(time(NULL)); //Seed the random number generator

	int a;
	printf("Slot Types:\n");
	for(a=0;a<=30;a++)
	{
		printf("_");
	}


	for(int i =0; i< 7; i++)
	{
		printf("\n| ");
		//This allocates in memory the space for the slots in each row of the board
		board[i] = malloc(7 * sizeof(struct slot));

		//For each slot it sets up the row and column number
		for(int j=0;j < 7; j++)
		{
			board[i][j].row = i;
			board[i][j].column = j;
			board[i][j].capacity = 0;

			/*Randomly set the type of each slot:*/
		    int dice = rand() % 3; //Roll the imaginary 3 sided dice

			switch(dice){

			case 0:
				  board[i][j].slotType = Ground;
				  break;
			case 1:
				  board[i][j].slotType = City;
				   break;
			case 2:
				  board[i][j].slotType = Hill;
				  break;

			}
		 printf("[%s] ", getSlotName(board[i][j].slotType)); //Print out the type of slot[i][j]
		}
	printf("|");
	}

	printf("\n");
	for(a=0;a<=30;a++)
	{
		printf("_");
	}

	//It sets up the adjacent slots for the slots that are
	//not at the borders. These slots have 4 adjacent elements
	for(int i=0; i< 7; i++)
	{
		for(int j=0;j < 7; j++)
		{
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last row, except the slots at the edges.

	for(int j = 0; j < 6; j++)
	{
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on top of them
		// because they are on the first row of the board
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on down them
		// because they are on the last row of the board
		board[6][j].right = &board[6][j+1];
		board[6][j].left = &board[6][j-1];
	    board[6][j].up = &board[5][j];
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last column, except the slots at the edges.

	for(int i = 1; i < 7 -1; i++)
	{
		//It sets up the adjacent slots for the slots that are in the first column.
		//These slots don't have an adjacent element on the left
		// because they are on the first column of the board
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];

		//It sets up the adjacent slots for the slots that are in the last column.
		//These slots don't have an adjacent element on the right
		// because they are on the last column of the board
		board[i][7-1].left = &board[i][5];
		board[i][7 -1].up = &board[i -1][6];
	    board[i][7 -1].down = &board[i+1][6];
	}


	//It sets up the adjacent slots for the slot at position (0,0).
	//This only has only 2 adjacent slots: right and down
	board[0][0].right = &board[0][1];
	board[0][0].down = &board[1][0];

	//It sets up the adjacent slots for the slot at position (0,6).
	//This only has only 2 adjacent slots: left and down
	board[0][6].left = &board[0][5];
	board[0][6].down = &board[1][6];

	//It sets up the adjacent slots for the slot at position (6 ,0).
	//This only has only 2 adjacent slots: up and right
	board[6][0].right = &board[6][1];
	board[6][0].up = &board[5][0];

	//It sets up the adjacent slots for the slot at position (6,6).
	//This only has only 2 adjacent slots: up and left
	board[6][6].up = &board[5][6];
	board[6][6].left = &board[6][5];





	//assigns a pointer to slot at position (0, 0)
	*upLeft = &board[0][0];
	//assigns pointer of pointer to slot at position (0, 7 -1)
	*upRight = &board[0][6];
	//assigns pointer of pointer to slot at position ( 7 -1,)
	*downLeft = &board[6][0];
	//assigns pointer of pointer to slot at position (7 -1, 7 -1)
    *downRight = &board[6][6];
}




/*
 * This function traverses the board to find a slot at a predefined
 * position (row, column)
 * Parameters:
 * 	row: the row in which the desired slot is located
 * 	column: the column in which the desired slot is located
 * 	initialSlot: the slot from which the slot search should start
 */
void reachDesiredElement(int row, int column, struct slot * initialSlot){

	bool found = false;
	//current slot
	struct slot * currentSlot = initialSlot;

	//prints the column and the row of the initial slot from which the search starts
	printf("Initial slot (%d, %d) -> \n",initialSlot->row,initialSlot->column);

	//while the slot is not found
	while(found == false){

		//if the row of the current slot is > of the row of the desired slot,
		//we move up
		if(currentSlot->row > row){
			//the current slot now points to the slot one row up
			currentSlot = currentSlot->up;
			//prints the column and the row of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the row of the current slot is < of the row of the desired slot,
		//we move down
		if(currentSlot->row < row){
			//the current slot now points to the slot one row down
			currentSlot = currentSlot->down;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the column of the current slot is > of the column of the desired slot,
		//we move left
		if(currentSlot->column > column){
			//the current slot now points to the slot one column left
			currentSlot = currentSlot->left;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);
		}

		//if the column of the current slot is < of the column of the desired slot,
		//we move right
		if(currentSlot->column < column){
			//the current slot now points to the slot one column right
			currentSlot = currentSlot->right;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the current slot is at a column and a row equal to the desired column and row, respectively
		// we found the slot
		if(currentSlot->column == column && currentSlot->row == row){
			//printf("Found\n");
			found = true;
		}

	}
}

//Short function which gets the appropriate slot-type string for the printf function in createBoard.
const char* getSlotName(enum sType slotType)
{
   switch (slotType)
   {
      case Ground:
    	  return "G";
    	  break;
      case City:
    	  return "C";
    	  break;
      case Hill:
    	  return "H";
    	  break;
   }
return "ERROR404";
}


