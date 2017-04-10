/*
 * userInteraction.c

 *
 *  Created on: 29 Mar 2017
 *      Author: Fionan, Mark
 */

#include <stdio.h>
#include "header.h"

//THis function takes as input the size of the board and the pointers
// to the integers representing the row and the column of the slot that
// the user want to retrieve
void getDesiredElement(int * row, int * col, int currentPLayer){
	printf("\n\nPlease enter the slot you would to begin at:\n");

		//it will cycle asking the user to insert the row
		//until the value of the desired row is >= 0 or < of the
		// size of the board
		do {
			printf("Row: ");
			scanf("%d", row);
			printf("%d\n", *row);
			if(*row < 0 || *row >= 7)
				printf("\nError: Incorrect row dimension, try again!\n");
		} while(*row < 0 || *row >= 7);

		//it will cycle asking the user to insert the column
		//until the value of the desired row is >= 0 or < of the
		// size of the board
		do {
			printf("Column: ");
			scanf("%d", col);
			printf("%d\n", *col);
			if(*col < 0 || *col >= 7)
				printf("\nError: Incorrect column dimension, try again!\n");
		} while(*col < 0 || *col >= 7);
}

void assignPlayers(int *numofplayers){

	unsigned int i;
	int choice;

	do{
		printf("\n\nHow many people are playing?\n");
		scanf("%d", &*numofplayers);
		}while(*numofplayers<2 || *numofplayers > MAXPLAYERS); //Ensures a valid input

	for(i=0;i<*numofplayers;i++)
		{
		do{
			printf("\nPlayer %d's Class: (1)Elf (2)Human (3)Ogre (4)Wizard:\n ", i+1);
			scanf("%d", &choice);
		   }while(choice!=1 && choice!=2 && choice!=3 && choice!=4); //Ensures a valid input

		//Note players[i].class can only be printed as an integer (0-3)
		switch(choice)
		  {
			case 1:
			{
			players[i].class = Elf;
			break;
			}

			{
			case 2:
			players[i].class = Human;
			break;
			}

			{
			case 3:
			players[i].class = Ogre;
			break;
			}

			{
			case 4:
			players[i].class = Wizard;
			break;
			}

		  }

		}


}
