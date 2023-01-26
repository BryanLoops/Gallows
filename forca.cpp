#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
using namespace std;

int main()
{
    string line;
    int total_lines = 0;
    vector<string> lines;

    srand(time(0));
    ifstream file("examples.txt");

    while (getline(file, line))
    {
        total_lines++;
        lines.push_back(line);
    }

    int random_number = rand() % total_lines;

    string secret = lines[random_number];
    string solution;

    file.close();

    for (int i = 0; i < secret.length(); i++)
    {
        solution.append("_");
    }

    bool game = true;
    string guess;
    int counter = 0;
    int forca = 4;
    string gallows[6][5] =
        {
            {" ", "_", "_", "_", " "},
            {"|", " ", " ", " ", " "},
            {"|", " ", " ", " ", " "},
            {"|", " ", " ", " ", " "},
            {"|", " ", " ", " ", " "},
            {"|", " ", " ", " ", " "}};

    cout << "A palavra tem " << secret.length() << " letras." << endl;

    while (game)
    {

        bool valid = false;

        // Identifica se a letra já não foi utilizada, se está na palavra, substitui as ocorrências e conta cada uma

        if (!solution.find(guess))
        {
            valid = true;

            while (valid)
            {
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        cout << gallows[i][j] << " \n"[j == 4];
                    }
                }

                cout << "Advinhe uma letra ou a forca te espera!" << endl;
                cin >> guess;
                for (int i = 0; i < guess.length(); i++)
                {
                    guess[i] = toupper(guess[i]);
                }

                for (int i = 0; i <= secret.length(); i++)
                {
                    if (secret.find(guess, i) == i)
                    {
                        solution.replace(secret.find(guess, i), 1, guess);
                        counter++;
                    }
                }
                valid = false;
                guess = "";
            }
        }
        else
        {
            cout << "Essa letra ja foi utilizada!" << endl;
        }

        // Parabeniza o jogador e mostra quais letras ele acertou para indicar o caminho correto
        if (counter > 0)
        {
            cout << "Parabens! Voce acertou " << counter << " letra(s)!" << endl;
            counter = 0;
        }
        else
        {
            if (forca > 1)
            {
                cout << "Voce errou!" << endl;
            }

            switch (forca)
            {
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

        cout << solution << endl;

        if (secret == solution)
        {
            cout << "Voce venceu e gastou " << 4 - forca << " tentativa(s)!" << endl;

            if (forca == 4)
            {
                cout << "Voce so pode ser um genio!!!" << endl;
            }
            else if (forca == 1)
            {
                cout << "Foi por pouco, em?" << endl;
            }
            else
            {
                cout << "Sera que voce consegue fazer melhor?" << endl;
            }

            game = false;
        }

        if (forca == 0)
        {
            cout << "Voce perdeu! :(" << endl;
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    cout << gallows[i][j] << " \n"[j == 4];
                }
            }
            game = false;
        }
    }
    return 0;
}