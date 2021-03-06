#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void findSlots(int reqDist, int currDist,  struct slot * currSlot, struct slot * foundSlots, int * count,  bool explored[7][7])
{

	//The base case: the current slot is at the required distance from the starting slot
	if(currDist == reqDist){
		//the current slot was not explored
		if(explored[currSlot->row][currSlot->column] == false)
		{
			//The next available position (indicated by count) at foundSlots points to the current slot
			*(foundSlots + *count) = *currSlot;
			//the counter is incremented
			(*count)++;
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
		}
	}
	//The recursive call: the current slot is at a distance that is less than the required distance (more slots still have to be traversed)
	else{
		//if the current slot has the up slot != NULL (i.e. the slot is not in the first row)
		if(currSlot->up != NULL)
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the up slot
			findSlots(reqDist, currDist +1,  currSlot->up, foundSlots, count, explored);
		if(currSlot->right != NULL)
			findSlots(reqDist, currDist +1,  currSlot->right, foundSlots, count, explored);
		if(currSlot->down != NULL)
			findSlots(reqDist, currDist +1,  currSlot->down, foundSlots, count, explored);
		if(currSlot->column != 0)
			findSlots(reqDist, currDist +1,  currSlot->left, foundSlots, count, explored);

	}

}


