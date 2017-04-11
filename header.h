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

typedef int bool;
enum { false , true };//This allows boolean logic to function as it should
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
int order;//Player's position in playersHere (this is for when a slot has more than one player)
bool dead;

int row;
int column;

int data;
struct Characters *next;
}players[1]; //Declare the array, players (initialize as being of size 1, but then dynamically expand this size later)


struct slot //Declare a new structure containing the stats for all players
{
  enum sType slotType; //Slot type (Ground, City or Hill) for each slot
  int playersHere[6]; //The player number (between 0 and numofplayers) that is currently occupying this slot
  int capacity;//The number of players occupying this slot (0-numofplayers)

  int row;
  int column;

  struct slot *left;
  struct slot *right;
  struct slot *up;
  struct slot *down;
};



//FUNCTION PROTOTYPES:
int getBoardSize();
void createBoard(struct slot **board, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);
void reachDesiredElement(int row, int column, struct slot * initialSlot);
const char* getSlotName(enum sType slotType);
const char* getClassName(enum cType class);
void assignPlayers(int *numofplayers);
void abilities(int numofplayers, int i);
void findSlots(int reqDist, int currDist, struct slot *currSlot, struct slot *foundSlots,
			   int *count, bool explored[7][7]);
void move(int numofplayers, int currentplayer, int row, int column,struct slot **board, int *numLeft);
void printBoard(struct slot **board);
void attack(int currentPlayer, int attackedPlayer, int attackType);

#endif /* OPERATIONS_H_ */
