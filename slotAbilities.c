#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "operations.h"

void slotAbilities(int numofplayers)
{
	int i;

	for(i=0;i<numofplayers;i++)
	{

		if(slot[players[i].currentslot].slottype == "Hill")//If the player is on a hill slot
   	     {
   	     	if(players[i].dexterity < 50)
   	     	{
   	     		players[i].strength -= 10;
   	     	}

   	     	else if(players[i].dexterity >= 60)
   	     	{
   	     		players[i].strength += 10;
   	     	}
    	        
        }

        if(slot[players[i].currentslot].slottype == "City")//If the player is on a city slot
   	     {
   	     	if(players[i].smartness > 60)
   	     	{
   	     		players[i].magic += 10;
   	     	}

   	     	else if(players[i].smartness <= 50)
   	     	{
   	     		players[i].dexterity -= 10;
   	     	}
    	        
        }
    }    

}