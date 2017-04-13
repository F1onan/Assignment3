#include <stdio.h>
#include "header.h"

void findSlots(int reqDist, int currDist, struct slot *currSlot, struct slot *foundSlots, int *count, bool explored[7][7])
{
	if(currDist == reqDist)
	{
		if(explored[currSlot->row][currSlot->column] == false)
		//If we havent already explored this slot
		{
			*(foundSlots + *count) = *currSlot;
			(*count)++;
			explored[currSlot ->row][currSlot->column] = true;
		}
	}

	else //recursively search through the adjacent slots
	{
		if(currSlot->up != NULL)
			findSlots(reqDist, currDist+1, currSlot->up, foundSlots, count, explored);
		if(currSlot->down != NULL)
			findSlots(reqDist, currDist+1, currSlot->down, foundSlots, count, explored);
		if(currSlot->left != NULL)
			findSlots(reqDist, currDist+1, currSlot->left, foundSlots, count, explored);
		if(currSlot->right != NULL)
			findSlots(reqDist, currDist+1, currSlot->right, foundSlots, count, explored);
	}
}
