#include <iostream>

#include "HangmanController.cpp"

int main() 
{
    // Palavra a ser adivinhada
    std::string word = "hello";
    
    // Número de tentativas
    int attempts = 6; 

    HangmanController game(word, attempts);
    game.playGame();

    return 0;
}
