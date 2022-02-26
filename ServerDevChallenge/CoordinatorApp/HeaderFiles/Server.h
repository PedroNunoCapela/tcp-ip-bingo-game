#ifndef COORDINATORAPP_SERVER_H
#define COORDINATORAPP_SERVER_H
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include<bits/stdc++.h>
#include <stdlib.h>
#include <set>
#include "../HeaderFiles/GameUtils.h"

using namespace  std;

/*this method is responsible for a socket creation
 * it uses socket() from socket programming library
 * AF_NET: it means we're using IPv4
 * SOCK_STREAM: connection type. In this case, it means TCP
 * 0: it means we're using IP protocol */
int createSocket();

/* This method is responsible for associating a local IP address and a socket
 * listeningSocket: socket we want to associate with a local IP adress
 * */
void bindSocket(int listeningSocket);

/*this method is responsible for handling socket connection
listeningSocket: socket we want to associate with a local IP adress*/
int waitConnection(int listeningSocket);

//Close socket
void closeSocket(int closingSocket);

/*this method checks for a valid connection in client's socket
* buf[]: communication buffer between two application sockets. It holds exchanged messages from both client and server apps
 * bytesReceived: how many bites were received by this application after clients sends a message
 * clientSocket: client's socket information*/
void checkConnection(char buf[], int clientSocket, int bytesReceived);


/* this method deals with messages sent from client application
 * buf[]: communication buffer between two application sockets. It holds exchanged messages from both client and server apps
 * bytesReceived: how many bites were received by this application after clients sends a message
 * clientSocket: client's socket information
 * */
void checkMessages(char buf[], int bytesReceived, int clientSocket);


/*this method sends a new game card to client's application
 * in order to use send() method, gameCard has to be converted to an array
 * clientSocket: client's socket information
 * gameCard: created game card*/
void sendGameCard(int clientSocket, set<int> gameCard);

#endif //COORDINATORAPP_SERVER_H
