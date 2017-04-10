/*
 * userInteraction.c

 *
 *  Created on: 29 Mar 2017
 *      Author: Fionan, Mark
 */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void assignPlayers(int *numofplayers){

	unsigned int i;
	int choice;
	struct Characters *first, *current, *last;

	do{
		printf("\n\nHow many people are playing?\n");
		scanf("%d", &*numofplayers);
		}while(*numofplayers<2 || *numofplayers > MAXPLAYERS); //Ensures a valid input

	//Dynamically allocate the appropriate space in memory for players[]
	  for (int i = 0; i < *numofplayers; i++)
	    {
	        last = malloc (sizeof (players));
	        last->data = i;
	        last->next = NULL;
	        if(i==0)
	        {
	        	first = last;
	        }
	        else
	        	current-> next = last;
	        current = last;
	    }

	    current = first;
	    while (current != NULL)
	    {
	        current = current->next;
	    }

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

//Function which prints the current position of players
void printBoard(struct slot **board)
{
	int a;
	printf("\nCurrent Board State:\n");
	for(a=0;a<=30;a++)
	{
		printf("_");
	}


	for(int i =0; i< 7; i++)
	{
		printf("\n| ");

		//For each slot it sets up the row and column number
		for(int j=0;j < 7; j++)
		{
		 printf("[");
		 if(board[i][j].capacity > 1)
		   printf("+"); //Print out the player here
		 else if(board[i][j].capacity == 1)
		   printf("%d", board[i][j].playersHere[0]+1); //Print out the player here
		 else if(board[i][j].capacity == 0)
			 printf(" ");
		 printf("] ");
		}
	printf("|");
	}

	printf("\n");
	for(a=0;a<=30;a++)
	{
		printf("_");
	}
	printf("\n\n");
}
