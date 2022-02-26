#include "../HeaderFiles/GameUtils.h"

using namespace std;

//method that draws a random number between 1-50
int drawRandNum() {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(1, 50); // define the range (1-50)

    return distr(gen); // returns generated number
}


/*this method just prints all the numbers in the game card*/
void printGameCard(int gameCard[]) {
    cout << "Generated game card:\n-> ";

    for (int i = 0; i < CARD_SIZE; i++) {
        cout << gameCard[i] << " ";
    }
    cout << endl;
}

