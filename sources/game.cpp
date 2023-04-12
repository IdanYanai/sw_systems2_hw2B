#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

#include "player.hpp"
#include "card.hpp"
#include "game.hpp"

namespace ariel {
    Game::Game(Player& p1, Player& p2) : p1(p1), p2(p2) {
        turns=0;
        p1Wins=0;
        p2Wins=0;
        draws=0;

        ofstream log ("log.txt");
        log.close();

        vector<card> fullStack;
        for(int i=0;i<4;i++)
            for(int j=1;j<14;j++) {
                fullStack.push_back(card(j,i));
                // cout << fullStack.back() << endl;
            }

        // cout << "Player 1 stack" << endl;
        int random;
        srand((unsigned int) time(0));
        for(int i=0;i<26;i++) {
            random = rand() % int(fullStack.size());
            p1.drawCard(fullStack[size_t(random)]);
            // cout << fullStack[size_t(random)] << endl;
            fullStack.erase(fullStack.begin() + int(random));
        }

        // cout << "Player 2 stack" << endl;
        for(int i=0;i<26;i++) {
            p2.drawCard(fullStack.back());
            // cout << fullStack.back() << endl;
            fullStack.pop_back();
        }
        // cout << "Game start" << endl;
    }

    void Game::playTurn() {
        if(p1.stacksize() == 0)
            throw logic_error("Game already finished");
        if(&p1 == &p2)
            throw invalid_argument("same player");

        ofstream log ("log.txt", ios::app);
        card& p1Card = p1.playCard();
        card& p2Card = p2.playCard();
        int onTable = 2;
        log << p1 << " played " << p1Card << ". ";
        log << p2 << " played " << p2Card << ". ";

        while(p1Card - p2Card == 0) {
            log << "Draw. ";
            draws++;
            if(p1.stacksize() < 2) {
                p1.addScore(onTable/2);
                p2.addScore(onTable/2);
                return;
            }

            p1Card = p1.playCard();
            p2Card = p2.playCard();

            p1Card = p1.playCard();
            p2Card = p2.playCard();

            onTable += 4;
            log << p1.getName() << " played " << p1Card.toString() << ". ";
            log << p2.getName() << " played " << p2Card.toString() << ". ";
        }

        // CHECK ACE
        if((p1Card.getNum() == 1) && (p2Card.getNum() != 2)) {
            p1.addScore(onTable);
            log << p1.getName() << " wins. \n";
            p1Wins++;
        }
        else if ((p1Card.getNum() != 2) && (p2Card.getNum() == 1))
        {
            p2.addScore(onTable);
            log << p2.getName() << " wins. \n";
            p2Wins++;
        }
        
        // if no one has an ACE
        else if(p1Card - p2Card > 0) {
            p1.addScore(onTable);
            log << p1.getName() << " wins. \n";
            p1Wins++;
        }
        else if(p1Card - p2Card < 0) {
            p2.addScore(onTable);
            log << p2.getName() << " wins. \n";
            p2Wins++;
        }
        turns++;
        log.close();
    }

    void Game::printLastTurn() {
        string lastLine;
        ifstream log ("log.txt");

        if(log.is_open()) {
            log.seekg(-2, ios_base::end);

            bool found = false;
            while(!found) {
                char ch;
                log.get(ch);

                if(ch == '\n')
                    found = true;
                else
                    log.seekg(-2, ios_base::cur);
            }
        }

        getline(log, lastLine);
        cout << "LAST TURN - " << lastLine << endl;
    }

    void Game::playAll() {
        while(p1.stacksize() != 0)
            playTurn();
    }

    void Game::printWiner() {
        if(p1.stacksize() == 0)
            if(p1.cardesTaken() > p2.cardesTaken())
                cout << p1 << " is the winner!" << endl;
            else if(p1.cardesTaken() < p2.cardesTaken())
                cout << p2 << " is the winner!" << endl;
            else
                cout << " its a tie!" << endl;
        else
            cout << "Game is not over yet!" << endl;
            
    }

    void Game::printLog() {
        string line;
        ifstream log ("log.txt");
        if(log.is_open())
            while(getline(log, line))
                cout << line << '\n';
        log.close();
    }

    void Game::printStats() {
        double percent;
        double totalBattles = p1Wins + p2Wins + draws;

        cout << "\n";
        cout << "--- GAME STATISTICS ---" << endl;
        cout << "Num of turns: " << turns << endl;
        cout << "Num of draws: " << draws << endl;
        percent = draws/totalBattles;
        cout << "Draw rate: " << to_string(percent) << "\n" << endl;

        cout << p1 << " statistics:" << endl;
        cout << "Cards taken: " << to_string(p1.cardesTaken()) << endl;
        percent = p1Wins/totalBattles;
        cout << "Winrate: " << to_string(percent) << "\n" << endl;
         
        cout << p2 << " statistics:" << endl;
        cout << "Cards taken: " << to_string(p2.cardesTaken()) << endl;
        percent = p2Wins/totalBattles;
        cout << "Winrate: " << to_string(percent) << endl;

    }
}