#include "../HeaderFiles/Server.h"

using namespace std;

/*this method is responsible for a socket creation
 * it uses socket() from socket programming library
 * AF_NET: it means we're using IPv4
 * SOCK_STREAM: connection type. In this case, it means TCP
 * 0: it means we're using IP protocol */
int createSocket() {

    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    //if socket() method doesn't return a positive value, it means something bad happen in socket creation process
    if (listening == -1) {
        //in that case, it displays an error messange and returns -1
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    } else
        //if there's no problem creating a new socket, return socket() value
        return listening;
}

/* This method is responsible for associating a local IP address and a socket
 * listeningSocket: socket we want to associate with a local IP adress
 * */
void bindSocket(int listeningSocket) {

    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listeningSocket, (sockaddr *) &hint, sizeof(hint));
}

/*this method is responsible for handling socket connection
listeningSocket: socket we want to associate with a local IP adress*/
int waitConnection(int listeningSocket) {

    // Tell Winsock the socket is for listening
    listen(listeningSocket, SOMAXCONN);

    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    //accepts pending connection and when it happens, it creates a new socket, returning it's descriptor
    int clientSocket = accept(listeningSocket, (sockaddr *) &client, &clientSize);

    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // port the client is connect on

    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    //displaying connection status
    if (getnameinfo((sockaddr *) &client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        cout << "Connected" << endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;

    }

    return clientSocket;
}

//Close socket (closing socket's descriptor)
void closeSocket(int closingSocket) {

    // Close listening socket
    close(closingSocket);
}


/*this method checks for a valid connection in client's socket
* buf[]: communication buffer between two application sockets. It holds exchanged messages from both client and server apps
 * bytesReceived: how many bites were received by this application after clients sends a message
 * clientSocket: client's socket information*/
void checkConnection(char buf[], int clientSocket, int bytesReceived) {

    //if received bytes value is invalid, method displays error message and terminates application
    if (bytesReceived == -1) {
        cerr << "Error in recv(). Quitting" << endl;
        abort();
    }

    //if client's application doesn't send more information, it means connection is lost, and client got disconnected
    if (bytesReceived == 0) {
        cout << "Client disconnected " << endl;
        //terminates application
        abort();
    }
}

/* this method deals with messages sent from client application
 * buf[]: communication buffer between two application sockets. It holds exchanged messages from both client and server apps
 * bytesReceived: how many bites were received by this application after clients sends a message
 * clientSocket: client's socket information
 * */
void checkMessages(char buf[], int bytesReceived, int clientSocket) {

    string newMessage = string(buf, 0, bytesReceived); //received data from client
    transform(newMessage.begin(), newMessage.end(), newMessage.begin(), ::toupper); //capitalizing messages sent from client

    //creates a new and empty game card.
    set<int> gameCard;

    //client sends GAME string whenever connection gets ready to proceed with the game
    if (newMessage == "GAME") {
        //filling new game card with sorted numbers
        while (gameCard.size() < CARD_SIZE) {
            /*Sets don't allow for duplicated values. So no duplicated values get inserted
            if there's a duplicated number, insertion won't happen and loop doesn't end.
            ensuring that game card contains 10 numbers and no duplicated values.*/
            gameCard.insert(drawRandNum());
        }

        //sending created game card to client
        sendGameCard(clientSocket, gameCard);
        return;
    }

    //client sends WON string when every sorted number is found in game card
    //when this happens, the game is over
    if (newMessage == "WON") {
        //sends end game message
        cout << "\nPlayer's card is complete :)" << endl;
        //terminate game
        exit(0);
    }


    //client applicarion sends NUM or OR strings whenever it's ready to receive a new sorted number
    if (newMessage == "NUM" || (newMessage == "OK")) {

        //creating a simple array in order to store new sorted number. send() requires a * char in order to work
        int n[1];
        n[0] = drawRandNum();   //drawing a new number

        //printing new sorted number
        cout << "New number: " << n[0] << endl;
        //sending sorted number to client's application
        send(clientSocket, n, sizeof(n), 0);
        return;
    }
    //something's wrong if received signal is neither a NUM nor a GAME string
    else {
        //error message
        cerr << "Error in recv(). Quitting" << endl;
        //terminate program
        abort();
    }
}


/*this method sends a new game card to client's application
 * in order to use send() method, gameCard has to be converted to an array
 * clientSocket: client's socket information
 * gameCard: created game card*/
void sendGameCard(int clientSocket, set<int> gameCard) {

    //this array holds game card values
    int newGameCard[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;

    //filling previous array with every number from gameCard set
    for (int num: gameCard) {
        newGameCard[i] = num;
        i++;
    }

    //printing game card in server's application
    printGameCard(newGameCard);
    //sending newly created and converted game card to client's application
    send(clientSocket, newGameCard, sizeof(newGameCard), 0);

}