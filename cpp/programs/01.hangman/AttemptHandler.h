#ifndef _ATTEMPT_HANDLER_
#define _ATTEMPT_HANDLER_

#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

class AttemptHandler {
    public:
        void setWord(std::string newWord);
        bool newAttempt(char attempt);
        void displayInformation();
        int getCharsLeft();

    private:
        bool isOldAttempt(char attempt);
        bool updateWord(char attempt);
        void printFailedAttempts();
        void printDiscoveredWord();

        std::set<char> m_attempted;
        std::set<char> m_failedAttempts;
        std::vector<char> m_discoveredWord;
        std::string m_word;
        int m_charsLeft;
};
#endif

