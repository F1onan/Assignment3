#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    		break;


       case 2:





 
    
       case 3: /*Magic attack*/

                if((players[currentPlayer].smartness + players[currentPlayer].magic) > 150)
                {
                    players[attackedPlayer-1].life -= ((players[currentPlayer].magic * 0.5) + (players[currentPlayer].smartness * 0.2));
                    printf("\nPlayers #%d's new life: %.0lf\n", attackedPlayer-1, players[attackedPlayer-1].life);
                }   


    	}
 
    }



