#ifndef COORDINATORAPP_GAMEUTILS_H
#define COORDINATORAPP_GAMEUTILS_H
#define CARD_SIZE 10
#include <set>
#include <cstdlib>
#include <ctime>    //access cpu clock
#include <iostream>
#include <array>
#include <random>

using namespace  std;

//method that draws a random number between 1-50
int drawRandNum();


/*this method just prints all the numbers in the game card*/
void printGameCard(int gameCard[]);


#endif //COORDINATORAPP_GAMEUTILS_H
