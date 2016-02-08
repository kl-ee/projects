#include <iostream>
#include "AttemptHandler.h"
#include "DisplayHandler.h"

using namespace std;

void clearScreen()
{
    for(int i = 0; i < 100; ++i)
        printf("\n");
}

int main()
{
    AttemptHandler attemptHandler;
    DisplayHandler displayHandler;

    // Get input word from user
    string input;
    cout << "Please input a phrase(phrase to guess): \033[0;30m" << endl;
    getline(cin, input);
    cout << "\033[0m" <<endl;
    attemptHandler.setWord(input);
    clearScreen();
    attemptHandler.displayInformation();
    displayHandler.displayImage();

    bool addPiece = false;
    bool continueGame = true;
    while(continueGame) {
        cout << "Next attempt: ";
        getline(cin, input);
        clearScreen();
        addPiece = !attemptHandler.newAttempt(input[0]);
        if(addPiece) {
            continueGame = displayHandler.addPiece();
        } else {
            continueGame = attemptHandler.getCharsLeft() > 0;
        }
        displayHandler.displayImage();
    }

    if(attemptHandler.getCharsLeft() == 0) {
        printf("CONGRATULATIONS! YOU WIN!\n");
    } else {
        printf("SORRY YOU ARE OUT OF TRIES.\n");
    }
}
