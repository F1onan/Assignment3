#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

void move(int numofplayers, int currentplayer, int row, int column, struct slot **board, int *numLeft)
{
    printf("\nPLLAYER %d'S ORDER = %d", currentplayer+1, players[currentplayer].order);
	unsigned int choice, moveChoice, i;
	bool upBlocked=false;
	bool downBlocked=false;
	bool rightBlocked=false;
	bool leftBlocked=false;
	bool validChoice=true;

	do{
	printf("Player #%d (%s), please select your option:\n", currentplayer+1, players[currentplayer].name);
	printf("1. Move to an adjacent slot\n");
    printf("2. Attack another player\n");
    printf("3. Quit the game\n");

	scanf("%d", &choice);
	}while(choice <1 || choice > 3);

	 switch(choice)
	 {
	   case 1:
	   {
			//Sort the int array playersHere:
			if(board[row][column].capacity>1)
			{
			int q = players[currentplayer].order-1;

			while (q<board[row][column].capacity-1)
			{
				board[row][column].playersHere[q]=board[row][column].playersHere[q+1];
				players[board[row][column].playersHere[q]].order--;
				q++;

			}
		}
		board[row][column].capacity--;//Old slot will hold one less

		//Find which directions (up, down, left, right) are impossible
		if(row == 0)
		  upBlocked = true;
		if(row == 6)
		  downBlocked = true;
		if(column == 0)
		  leftBlocked = true;
		if (column == 6)
		   rightBlocked = true;

		do{
		 validChoice = true;
		 printf("Select a slot to move to:\n");

		 do{
		 if(upBlocked == false)
			 printf("1. (%d, %d)\n", row-1, column);
		 if(downBlocked == false)
			 printf("2. (%d, %d)\n", row+1, column);
		 if(leftBlocked == false)
			 printf("3. (%d, %d)\n", row, column-1);
		 if(rightBlocked == false)
			 printf("4. (%d, %d)\n", row, column+1);

		 scanf("%d", &moveChoice);
		 }while(moveChoice<1 || moveChoice>4);

		 if(moveChoice== 1 && upBlocked == true)
		 {
			 printf("\nInvalid slot choice: Cannot move up!\n");
		 	 validChoice = false;
		 }
		 if(moveChoice== 2 && downBlocked == true)
		 {
			 printf("\nInvalid slot choice: Cannot move down!\n");
		 	 validChoice = false;
		 }
	     if(moveChoice== 3 && leftBlocked == true)
		 {
			 printf("\nInvalid slot choice: Cannot move left!\n");
		 	 validChoice = false;
		 }
		 if(moveChoice== 4 && rightBlocked == true)
		 {
			 printf("\nInvalid slot choice: Cannot move right!\n");
		 	 validChoice = false;
		 }

		}while(validChoice == false);

		switch(moveChoice)
		{
		case 1://move up
			row--;
			break;
		case 2: //move down
			row++;
			break;
		case 3://move left
			column--;
			break;
		case 4: //move right
			column++;
			break;
		}


		players[currentplayer].row = row;
		players[currentplayer].column = column;

		//Modify player's cababilties:
		if(board[row][column].slotType == Hill)
		{
			if(players[currentplayer].dexterity < 50 )
				players[currentplayer].strength-=10;
			if(players[currentplayer].dexterity >= 60 )
				players[currentplayer].strength+=10;
		}
		else if(board[row][column].slotType == City)
		{
			if(players[currentplayer].smartness > 60 )
				players[currentplayer].magic+=10;
			if(players[currentplayer].smartness <= 50 )
				players[currentplayer].dexterity-=10;
		}


		board[row][column].capacity++;
		int k = board[row][column].capacity-1; //k is the position in playershere that will be filled by the new player
		players[currentplayer].order=k;

		board[row][column].playersHere[k] = currentplayer;
		//If there are two players on the one slot (ie capacity == 2) then the second player will be stored
		//in board[][].playershere[1]. Likewise, if the slot will now have 3 players then the newest player will be at playersHere[2].
		//For playersHere[i], i will always be the capacity of the slot - 1.

		printf("\n%s's new slot: (%d, %d)\n", players[currentplayer].name, players[currentplayer].row, players[currentplayer].column);
		break;
	   }//End of choice: 1

	   case 2:
	   {

		  // printf("\nThe row above this slot is %d",board[row][column].up->row);


		   unsigned int attackChoice;
		   do{
		   printf("Select attack type:\n");
		   printf("1. Near Attack\n");
		   printf("2. Distant Attack\n");
		   printf("3. Magic Attack\n");

		   scanf("%d", &attackChoice);
		   }while(attackChoice<1 || attackChoice>3);

		     if(attackChoice==1)
		     {
			    if(row == 0 || board[row][column].up->capacity == 0)
			        upBlocked=true;
			    if(row == 6 || board[row][column].down->capacity == 0)
			    	downBlocked=true;
			    if(column == 0 || board[row][column].left->capacity == 0)
			    	leftBlocked=true;
			    if(column == 6 || board[row][column].right->capacity == 0)
			    	rightBlocked=true;
			    if(board[row][column].capacity==1 && upBlocked==true && downBlocked==true && leftBlocked==true && rightBlocked==true)
			    {
			    	printf("\nNo nearby players found!\n");
			    	validChoice=false;
			    }
			    else
			    {
			    	printf("\nSelect a player to attack:\n");
			    	if(upBlocked==false)
			    	{
			    		for(i=0; i<board[row][column].up->capacity; i++)
			    		  printf("Player %d\n", board[row][column].up->playersHere[i]+1);
			    	}
			    	if(downBlocked==false)
			    	{
			    		for(i=0; i<board[row][column].down->capacity; i++)
			    		  printf("Player %d\n", board[row][column].down->playersHere[i]+1);
			    	}
			    	if(leftBlocked==false)
			    	{
			    		for(i=0; i<board[row][column].left->capacity; i++)
			    		  printf("Player %d\n", board[row][column].left->playersHere[i]+1);
			    	}
			    	if(rightBlocked==false)
			    	{
			    		for(i=0; i<board[row][column].right->capacity; i++)
			    		  printf("Player %d\n", board[row][column].right->playersHere[i]+1);
			    	}
			    	if(board[row][column].capacity>1)
			    	{
			    		for(i=0; i<board[row][column].capacity; i++)
			    		{
			    		  if(players[currentplayer].order != i)
			    		    printf("Player %d\n", board[row][column].playersHere[i]+1);
			    		}
			    	}

			    }
			    break;

		     }

		     if(attackChoice==2)
		     {
			   //CODE FOR DISTANT ATTACK
			   break;
		     }

		     if(attackChoice==3)
		     {
			   //CODE FOR MAGIC ATTACK
			   break;
		     }

		   break;
	   }//End of choice: 2

	   case 3://Quit the game
	   {
		   players[currentplayer].dead=true; //rip
		   break;
	   }

	 }//End of switch(choice)
}
