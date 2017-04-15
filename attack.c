#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void attack(int currentPlayer, int attackedPlayer, int attackType, struct slot **board, int *numLeft)
{
	//NOTE: attackedPlayer is the player NUMBER (Player 1 = 1 etc.)
	//		while currentPlayer is the player POSITION (i.e. Player 1 = 0)

	printf("\nPlayer %d attacks Player %d.", currentPlayer+1, attackedPlayer);

	switch(attackType)
	{
	case 1://near-attack
		if(players[attackedPlayer-1].strength<=70)
		{
			players[attackedPlayer-1].life -= 0.5 * players[currentPlayer].strength;
			printf("\nPlayers #%d's new life: %.0lf\n", attackedPlayer, players[attackedPlayer-1].life);
		}
		if(players[attackedPlayer-1].strength>70)
		{
			players[currentPlayer].life-= 0.3 * players[attackedPlayer-1].strength;
			printf("\nPlayers #%d's new life: %.0lf\n", currentPlayer+1, players[currentPlayer].life);
		}
		break;

	case 2://distant attack
		if(players[attackedPlayer-1].dexterity>=players[currentPlayer].dexterity)
		{
			printf("\nPlayers #%d's life: %.0lf (unchanged)\n", attackedPlayer, players[attackedPlayer-1].life);
		}
		else if(players[attackedPlayer-1].dexterity<players[currentPlayer].dexterity)
		{
			players[attackedPlayer-1].life-= 0.3 * players[currentPlayer].strength;
			printf("\nPlayers #%d's new life: %.0lf\n", attackedPlayer, players[attackedPlayer-1].life);
		}
		break;


	case 3://magic-attack
		  if((players[currentPlayer].smartness + players[currentPlayer].magic) > 150)
		  {
			  players[attackedPlayer-1].life -= ((players[currentPlayer].magic * 0.5) + (players[currentPlayer].smartness * 0.2));
		      printf("\nPlayers #%d's new life: %.0lf\n", attackedPlayer, players[attackedPlayer-1].life);
		  }
		  else
		  {
			  printf("\nPlayer %d does not have the right capabilities to attack player %d\n", currentPlayer+1, attackedPlayer);
		  }
		break;
	}

	 //If the attacked player died
	 if(players[attackedPlayer-1].life<1)
	 {
		int q = players[attackedPlayer-1].order-1;
		int row = players[attackedPlayer-1].row;
		int column = players[attackedPlayer-1].column;

		while (q<board[row][column].capacity-1)
		{
			board[row][column].playersHere[q]=board[row][column].playersHere[q+1];
			players[board[row][column].playersHere[q]].order--;
			q++;
		}

		board[row][column].capacity--;
		players[attackedPlayer-1].dead=true;
		(*numLeft)--;
		printf("\nPlayer %d was killed by player %d!", attackedPlayer, currentPlayer+1);
	 }
}
