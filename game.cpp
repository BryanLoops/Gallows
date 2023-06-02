#include "game.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <cctype>

Game::Game() : totalLines(0), counter(0), forca(4) {
    std::string gallows[6][5] = {
        {" ", "_", "_", "_", " "},
        {"|", " ", " ", " ", " "},
        {"|", " ", " ", " ", " "},
        {"|", " ", " ", " ", " "},
        {"|", " ", " ", " ", " "},
        {"|", " ", " ", " ", " "}
    };
}

void Game::play() {
    loadWords();
    initializeSolution();

    std::cout << "A palavra tem " << secret.length() << " letras." << std::endl;

    while (!isGameOver()) {
        bool valid = false;
        std::string guess;

        if (!solution.find(guess)) {
            valid = true;

            while (valid) {
                printGallows();

                std::cout << "Advinhe uma letra ou a forca te espera!" << std::endl;
                std::cin >> guess;
                for (int i = 0; i < guess.length(); i++) {
                    guess[i] = toupper(guess[i]);
                }

                updateSolution(guess);
                valid = false;
                guess = "";
            }
        } else {
            std::cout << "Essa letra ja foi utilizada!" << std::endl;
        }

        if (counter > 0) {
            std::cout << "Parabens! Voce acertou " << counter << " letra(s)!" << std::endl;
            counter = 0;
        } else {
            if (forca > 1) {
                std::cout << "Voce errou!" << std::endl;
            }

            switch (forca) {
                case 4:
                    gallows[1][3].replace(0, 1, "O");
                    break;
                case 3:
                    gallows[2][2].replace(0, 1, "/");
                    gallows[2][4].replace(0, 1, "\\");
                    break;
                case 2:
                    gallows[2][3].replace(0, 1, "|");
                    break;
                case 1:
                    gallows[3][2].replace(0, 1, "/");
                    gallows[3][4].replace(0, 1, "\\");
                    break;
            }
            forca--;
        }

        printSolution();

        if (secret == solution) {
            printResult();
            break;
        }
    }
}

void Game::loadWords() {
    std::string line;
    srand(time(0));
    std::ifstream file("examples.txt");

    while (getline(file, line)) {
        totalLines++;
        lines.push_back(line);
    }

    int random_number = rand() % totalLines;
    secret = lines[random_number];

    file.close();
}

void Game::initializeSolution() {
    for (int i = 0; i < secret.length(); i++) {
        solution.append("_");
    }
}

bool Game::isGuessValid(const std::string& guess) {
    return true;
}

void Game::updateSolution(const std::string& guess) {
    for (int i = 0; i <= secret.length(); i++) {
        if (secret.find(guess, i) == i) {
            solution.replace(secret.find(guess, i), 1, guess);
            counter++;
        }
    }
}

bool Game::isGameOver() {
    return forca == 0 || secret == solution;
}

void Game::printGallows() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << gallows[i][j] << " \n"[j == 4];
        }
    }
}

void Game::printSolution() {
    std::cout << solution << std::endl;
}

void Game::printResult() {
    std::cout << "Voce ";

    if (forca == 0) {
        std::cout << "perdeu! :(" << std::endl;
        printGallows();
    } else {
        std::cout << "venceu e gastou " << 4 - forca << " tentativa(s)!" << std::endl;

        if (forca == 4) {
            std::cout << "Voce so pode ser um genio!!!" << std::endl;
        } else if (forca == 1) {
            std::cout << "Foi por pouco, em?" << std::endl;
        } else {
            std::cout << "Sera que voce consegue fazer melhor?" << std::endl;
        }
    }
}
