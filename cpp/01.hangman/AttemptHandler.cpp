#include "AttemptHandler.h"

// public
void
AttemptHandler::setWord(std::string newWord)
{
    m_word = newWord;
    m_discoveredWord.reserve(newWord.size()+1);
    for(int i = 0; i < newWord.size(); ++i)
        m_discoveredWord.push_back('_');
    m_charsLeft = newWord.size();
}

// public - return(true) means we do not add a piece to the image
bool
AttemptHandler::newAttempt(char attempt)
{
    // Check if we've attempted this char before
    if(isOldAttempt(attempt)) {
        // Print attempts and word
        displayInformation();
        return(true);
    }
    // We haven't attempted this before, add it to the attempted list
    m_attempted.insert(attempt);

    // Check if the char is in our word, and update if it is
    bool foundChar = false;
    foundChar = updateWord(attempt);

    // Print attempts and word
    displayInformation();

    return(foundChar);
}

// public
void
AttemptHandler::displayInformation()
{
    // print the attempts
    printFailedAttempts();

    // print the word as we know it
    printDiscoveredWord();
}

// public
int
AttemptHandler::getCharsLeft()
{
    return(m_charsLeft);
}

// private
bool
AttemptHandler::isOldAttempt(char attempt)
{
    auto itr = m_attempted.find(attempt);
    if(itr == m_attempted.end())
        return(false);
    return(true);
}

// private
bool
AttemptHandler::updateWord(char attempt)
{
    bool found = false;
    for(int i = 0; i < m_word.size(); ++i) {
        if(m_word[i] == attempt) {
            m_discoveredWord[i] = attempt;
            m_charsLeft--;
            found = true;
        }
    }
    if(!found) {
        m_failedAttempts.insert(attempt);
    }
    return(found);
}

// private
void
AttemptHandler::printFailedAttempts()
{
    printf("Failed attempts: [");

    // Print the first character
    if(!m_failedAttempts.empty()) {
        printf(" %c ", *m_failedAttempts.begin());
        // Print all the others with "|" separating them
        for(auto itr = ++m_failedAttempts.begin();
                itr != m_failedAttempts.end(); ++itr) {
            printf("| %c ", *itr);
        }
    }
    printf("]\n\n");
}

// private
void
AttemptHandler::printDiscoveredWord()
{
    printf("Word(s) so far: ");
    // We're going to be lazy and print an extra space at the end
    std::for_each(m_discoveredWord.begin(), m_discoveredWord.end(),
            [] (char &c) {
                printf("%c ", c);
            });
    printf("\n");
}

