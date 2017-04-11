#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

void move(int numofplayers, int currentPlayer, int row, int column, struct slot **board, int *numLeft)
{
	unsigned int choice, moveChoice, i;
	bool upBlocked=false;
	bool downBlocked=false;
	bool rightBlocked=false;
	bool leftBlocked=false;
	bool validChoice=true;//We'll used this boolean value to ensure valid inputs with a do/while loop

	do{
	printf("Player #%d (%s), please select your option:\n", currentPlayer+1, players[currentPlayer].name);
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
			int q = players[currentPlayer].order-1;

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


		players[currentPlayer].row = row;
		players[currentPlayer].column = column;

		//Modify player's cababilties:
		if(board[row][column].slotType == Hill)
		{
			if(players[currentPlayer].dexterity < 50 )
				players[currentPlayer].strength-=10;
			if(players[currentPlayer].dexterity >= 60 )
				players[currentPlayer].strength+=10;
		}
		else if(board[row][column].slotType == City)
		{
			if(players[currentPlayer].smartness > 60 )
				players[currentPlayer].magic+=10;
			if(players[currentPlayer].smartness <= 50 )
				players[currentPlayer].dexterity-=10;
		}


		board[row][column].capacity++;
		int k = board[row][column].capacity-1; //k is the position in playershere that will be filled by the new player
		players[currentPlayer].order=k;

		board[row][column].playersHere[k] = currentPlayer;
		//If there are two players on the one slot (ie capacity == 2) then the second player will be stored
		//in board[][].playershere[1]. Likewise, if the slot will now have 3 players then the newest player will be at playersHere[2].
		//For playersHere[i], i will always be the capacity of the slot - 1.

		printf("\n%s's new slot: (%d, %d)\n", players[currentPlayer].name, players[currentPlayer].row, players[currentPlayer].column);
		break;
	   }//End of choice: 1

	   case 2:
	   {
		   int attackablePlayers[numofplayers-1];//Int array which holds the numbers of players that can be attacked
		   unsigned int b = 0;//Counter for attackablePlayers.
		   int attackedPlayer;//The NUMBER of the player chosen to be attacked

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
			    	//If the player tries to choose near-attack, when there are no nearby players
			    	printf("\nNo nearby players found! Player %d passes this round\n", currentPlayer+1);
			    	break;
			    }
			    else
			    {
			    	printf("\nEnter the number of the player you would like to attack. Possible choices:\n");
			    	if(upBlocked==false)
			    	{
			    		for(i=0; i<board[row][column].up->capacity; i++)
			    		    attackablePlayers[b++] = board[row][column].up->playersHere[i]+1;

			    	}
			    	if(downBlocked==false)
			    	{
			    		for(i=0; i<board[row][column].down->capacity; i++)
			    			attackablePlayers[b++] = board[row][column].down->playersHere[i]+1;
			    	}
			    	if(leftBlocked==false)
			    	{
			    		for(i=0; i<board[row][column].left->capacity; i++)
			    			attackablePlayers[b++] = board[row][column].left->playersHere[i]+1;
			    	}
			    	if(rightBlocked==false)
			    	{
			    		for(i=0; i<board[row][column].right->capacity; i++)
			    			attackablePlayers[b++] = board[row][column].right->playersHere[i]+1;
			    	}
			    	if(board[row][column].capacity>1)
			    	{
			    		for(i=0; i<board[row][column].capacity; i++)
			    		{
			    		  if(players[currentPlayer].order != i)//Don't include the player himself
			    			  attackablePlayers[b++] = board[row][column].playersHere[i]+1;
			    		}
			    	}

			    }

			    do{
			    validChoice=false;
			    for(i=0; i<b; i++)
			    	printf("Player %d\n", attackablePlayers[i]);
			    scanf("%d", &attackedPlayer);
			    for(i=0;i<b;i++)
			    {
			    	if(attackablePlayers[i]==attackedPlayer)
			    		validChoice=true;
			    }
			    }while(validChoice==false);

			    attack(currentPlayer, attackedPlayer, 1);

			    break;
		     }

		     if(attackChoice==2)
		     {


		     break;
		     }

		     if(attackChoice==3)
		     {
		       printf("\nEnter the number of the player you would like to attack. Possible choices:\n");

		       for(i=0; i<numofplayers; i++)
		       {
		    	   printf("Player %d\n", players[i]);
		       }

		       scanf("%d", &attackedPlayer);

		       attack(currentPlayer, attackedPlayer, 3);

			   break;
		     }

		   break;
	   }//End of choice: 2

	   case 3://Quit the game
	   {
		   players[currentPlayer].dead=true; //rip
		   break;
	   }

	 }//End of switch(choice)
}
