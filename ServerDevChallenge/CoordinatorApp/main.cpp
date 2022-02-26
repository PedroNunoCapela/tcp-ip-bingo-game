#include "HeaderFiles/GameUtils.h"
#include "HeaderFiles/Server.h"

using namespace std;

int main(int argc, char *argv[])
{

    // Create a socket
    int listeningSocket = createSocket();

    //Bind socket with IP address and port
    bindSocket(listeningSocket);

    //Waiting for connection
    int clientSocket = waitConnection(listeningSocket);

    // Close the socket
    closeSocket(listeningSocket);


    char buf[4096];     //buffer that stores client's messages
    //int  buf[4096];
    int bytesReceived = 0;

    while (true)
    {
        memset(buf, 0, 4096);
        // Wait for client to send data
        bytesReceived = recv(clientSocket, buf, 4096, 0);

        //checks client's connection
        checkConnection(buf, clientSocket, bytesReceived);

        //deals with client's messages
        checkMessages(buf, bytesReceived, clientSocket);

    }

    // Close the socket
    closeSocket(clientSocket);

    return 0;
}