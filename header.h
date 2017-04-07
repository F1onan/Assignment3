/*
 * operations.h
 *
 *  Created on: 26 Feb 2017
 *  Author: Fionan(16360121), Mark()
 *  Header file containing function prototypes and structs
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#define MAXNAMELEN 25//Max length of a player's name
#define MAXPLAYERS 6//Max number of players
#define MAXSLOTS 20 //Max number of slots

typedef int bool;
enum { false , true };
enum sType {Ground, City, Hill};
enum cType {Elf, Human, Ogre, Wizard};

struct Characters //Declare a new structure containing the stats for all players
{

enum cType class;
float life; //Each player's life points
char name[MAXNAMELEN];// The player's name
int smartness;
int strength;
int magic;
int luck;
int dexterity;
int currentslot;
int data;
struct Characters *next;
}players[1]; //Declare the array, players (initialize as being of size 1, but then dynamically expand this size later)


struct slot //Declare a new structure containing the stats for all players
{
  enum sType slotType; //Slot type (Ground, City or Hill) for each slot
  int full; //Boolean array to track which slot positions are full (1 = full, 0 = empty)
  int currentplayer; //The player number (between 0 and numofplayers) that is currently occupying this slot
  int data;
  struct Slotstruct *next;

  int row;
  int column;
  struct slot *left;
  struct slot *right;
  struct slot *up;
  struct slot *down;
}slot[1];


//FUNCTION PROTOTYPES:
int getBoardSize();
void getDesiredElement(int * row, int * col, int currentPlayer);
void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);
void reachDesiredElement(int row, int column, struct slot * initialSlot);
const char* getSlotName(enum sType slotType);
const char* getClassName(enum cType class);
void assignPlayers(int *numofplayers);
void abilities(int numofplayers, int i);

#endif /* OPERATIONS_H_ */
