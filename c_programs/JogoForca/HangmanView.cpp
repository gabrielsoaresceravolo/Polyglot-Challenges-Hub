#include <iostream>

// Visualização: interação com o usuário
class HangmanView 
{
    public:
        void displayHangman(int attemptsLeft) 
        {
            std::cout << "Tentativas restantes: " << attemptsLeft << std::endl;
        }

        void displayGuessedWord(const std::string& guessedWord) 
        {
            std::cout << "Palavra: " << guessedWord << std::endl;
        }

        void displayEndGame(bool victory, const std::string& word) 
        {
            if (victory)
                std::cout << "Parabéns, você venceu! A palavra era: " << word << std::endl;
            else
                std::cout << "Você perdeu! A palavra era: " << word << std::endl;
        }

        char getGuess() 
        {
            std::cout << "Digite uma letra: ";
            char guess;
            std::cin >> guess;
            return guess;
        }
};
