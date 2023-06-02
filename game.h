#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

class Game {
public:
    Game();
    void play();

private:
    void loadWords();
    void initializeSolution();
    bool isGuessValid(const std::string& guess);
    void updateSolution(const std::string& guess);
    bool isGameOver();
    void printGallows();
    void printSolution();
    void printResult();

    std::vector<std::string> lines;
    std::string secret;
    std::string solution;
    std::string guess;
    int totalLines;
    int counter;
    int forca;
    std::string gallows[6][5];
};

#endif  // GAME_H
