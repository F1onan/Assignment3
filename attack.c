#include <stdio.h>
#include "header.h"

void attack(int currentPlayer, int attackedPlayer, int attackType)
{
	switch(attackType)
	{
	case 1://near-attack
		if(players[attackedPlayer-1].strength<=70)
		{
			players[attackedPlayer-1].life -= 0.5 * players[currentPlayer].strength;
			printf("\nPlayers #%d's new life: %.0lf\n", attackedPlayer-1, players[attackedPlayer-1].life);
		}
		if(players[attackedPlayer].strength>70)
		{
			players[currentPlayer].life-= 0.3 * players[attackedPlayer-1].life;
			printf("\nPlayers #%d's new life: %.0lf\n", currentPlayer, players[currentPlayer].life);
		}
	}

	//case 2://distant-attack

//	case 3://magic-attack

}
