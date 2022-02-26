#include "HeaderFiles/Utils.h"
#include "HeaderFiles/Client.h"

using namespace std;

int main() {
    //	Create a socket
    int clientSocket = createSocket();

    //	Create a hint structure for the server we're connecting with
    sockaddr_in hint = createHint();

    //	Connect to the server on the socket
    if (conToServer(clientSocket, hint) == 0) {
        //send GAME request
        string game = "GAME";
        send(clientSocket, game.c_str(), game.size(), 0);
    }


    string numSignal = "NUM";      //string sent to server, in order for it to keep sending numbers.
    string wonSignal = "WON";      //lets server know that client won and the game is over.
    set<int> gameCard;

    while (true) {

        int buf[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};       //buffer that holds all data sent from server's application
        int bytesReceived = 0;
        //stores the number of bytes received in every new message sent by serve's application
        bytesReceived = recv(clientSocket, buf, sizeof(buf), 0);


        set<int> recData;
        //converting received data to a set. 
        for (int n: buf) {
            recData.insert(n);
        }

        switch (recData.size()) {
            case 2: {
                /*when server sends a single number, it's actually an array filled with both the new number and zeros.
                since sets don't allow for duplicated values, whenever we receive a number, the set will be populated with both that number and a zero.
                that's why we need to check for size 2.
                it means we received a number. Not a card. */

                int receivedNum = buf[0];

                //checking if game card contains newly received number
                gameCard = lookForNumber(gameCard, receivedNum);


                //if game card is empty
                if (gameCard.size() == 0) {
                    cout << "No more numbers!\n *** Bingo! :) ***" << endl;
                    //send back "WON"
                    send(clientSocket, wonSignal.c_str(), wonSignal.size(), 0);
                    //terminate program
                    exit(0);
                } else {
                    //sends NUM signal so server keeps sending numbers
                    send(clientSocket, numSignal.c_str(), numSignal.size(), 0);
                }
                break;
            }

            case 10: {
                /*if received message is not a number, it can only be a game card
                in order to validate if card is ok, we only need to check if it has 10 elements.
                because it is a set, we already know it cannot contain duplicated values.*/
                gameCard = recData;
                string cardOk = "OK";

                //print game card
                printCard(gameCard);
                //send confirmation, card is ok.
                send(clientSocket, cardOk.c_str(), cardOk.size(), 0);
                break;
            }

            default: {
                /*if received data isn't a number or a card, somethins wrong.
                display error message*/
                cerr << "Error in recv(). Quitting" << endl;
                //terminate program
                abort();
                break;
            }

        }

    }
    //	Close the socket
    close(clientSocket);

    return 0;
}
