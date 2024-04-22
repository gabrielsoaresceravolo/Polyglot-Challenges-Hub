#include <iostream>

class HangmanModel 
{
    private:
        std::string word;
        std::string guessedWord;
        int attemptsLeft;

    public:
        HangmanModel(const std::string& word, int attempts) : word(word), attemptsLeft(attempts) 
        {
            guessedWord = std::string(word.length(), '_');
        }

        bool guess(char letter) 
        {
            bool found = false;
            for (size_t i = 0; i < word.length(); ++i) 
            {
                if (word[i] == letter) 
                {
                    guessedWord[i] = letter;
                    found = true;
                }
            }
            if (!found)
                attemptsLeft--;
            return found;
        }

        const std::string& getGuessedWord() const 
        {
            return guessedWord;
        }

        int getAttemptsLeft() const 
        {
            return attemptsLeft;
        }

        bool isWordGuessed() const 
        {
            return guessedWord == word;
        }
};
