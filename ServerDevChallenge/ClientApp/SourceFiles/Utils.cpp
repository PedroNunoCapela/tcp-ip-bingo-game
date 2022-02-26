#include "../HeaderFiles/Utils.h"


/*this method looks in the game card for the received number
if number is found, it removes it from the game card and returns the updated game card
gameCard: card game
receivedNumber: number we're looking for*/
set<int> lookForNumber(set<int> gameCard, int receivedNumber){
    //if number is found in the card
    if(gameCard.find(receivedNumber) != gameCard.end()){
        //scratch number from card.
        gameCard.erase(gameCard.find(receivedNumber));

        //displays found message and how many numbers left for the card to be completed
        cout << receivedNumber << " found!\n" << gameCard.size() << " numbers left\n" << endl;
    }
    //returns updated game card
    return gameCard;


}


/*this method prints every number contained in game card*/
void printCard(set<int> gameCard){
    cout << "This is your game card:\n      -> ";
    for(int n : gameCard){
        cout << n << " ";
    }
    cout << endl;
}