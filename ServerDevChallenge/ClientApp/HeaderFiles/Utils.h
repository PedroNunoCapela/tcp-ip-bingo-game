#ifndef CLIENTAPP_UTILS_H
#define CLIENTAPP_UTILS_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <set>
#include <algorithm>    //user for find()
#include <iterator>     //used for begin() and end()
#define CARD_SIZE 10

using namespace std;

//prints every number contained in game card
void printCard(set<int> gameCard);

// checks if game card contains the received number
set<int> lookForNumber(set<int>  gameCard, int receivedNumber);



#endif //CLIENTAPP_UTILS_H
