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
#include <stdint.h>
#include "../HeaderFiles/Utils.h"

#define CARD_SIZE 10

using namespace  std;

/*this method is responsible for a socket creation
 * it uses socket() from socket programming library
 * AF_NET: it means we're using IPv4
 * SOCK_STREAM: connection type. In this case, it means TCP
 * 0: it means we're using IP protocol */
int createSocket();

/*information for socket connection*/
sockaddr_in createHint();

/*this method handles the connection between client and server app*/
int conToServer(int sock, sockaddr_in hint);

//Close socket
void closeSocket(int closingSocket);


#endif //COORDINATORAPP_SERVER_H
