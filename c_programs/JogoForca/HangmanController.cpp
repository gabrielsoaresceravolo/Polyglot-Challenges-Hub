#include <iostream>

#include "HangmanModel.cpp"
#include "HangmanView.cpp"

// Controle: coordenação do jogo
class HangmanController 
{
    private:
        HangmanModel model;
        HangmanView view;

    public:
        HangmanController(const std::string& word, int attempts) : model(word, attempts) {}

        void playGame() 
        {
            while (true) 
            {
                view.displayHangman(model.getAttemptsLeft());
                view.displayGuessedWord(model.getGuessedWord());

                char guess = view.getGuess();

                bool found = model.guess(guess);
                if (model.isWordGuessed()) 
                {
                    view.displayEndGame(true, model.getGuessedWord());
                    break;
                }
                if (!found && model.getAttemptsLeft() == 0) 
                {
                    view.displayEndGame(false, model.getGuessedWord());
                    break;
                }
            }
        }
};
