#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

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
            p1.stack.push_back(fullStack[size_t(random)]);
            // cout << fullStack[size_t(random)] << endl;
            fullStack.erase(fullStack.begin() + int(random));
        }

        // cout << "Player 2 stack" << endl;
        for(int i=0;i<26;i++) {
            p2.stack.push_back(fullStack.back());
            // cout << fullStack.back() << endl;
            fullStack.pop_back();
        }
        cout << "Game start" << endl;
    }

    void Game::playTurn() {
        if(p1.stack.size() == 0)
            cout << "Game already finished" << endl;

        string toAppend = "";
        card& p1Card = p1.stack.back();
        card& p2Card = p2.stack.back();
        p1.stack.pop_back();
        p2.stack.pop_back();
        int onTable = 2;
        toAppend.append(p1.getName() + string(" played ") + p1Card.toString() + string(". "));
        toAppend.append(p2.getName() + string(" played ") + p2Card.toString() + string(". "));
        cout << toAppend << endl;

        while(p1Card - p2Card == 0) {
            toAppend += "Draw. ";
            draws++;
            if(p1.stack.size() < 2) {
                log.push_back(toAppend);
                return;
            }
            p1.stack.pop_back();
            p2.stack.pop_back();
            p1Card = p1.stack.back();
            p2Card = p2.stack.back();
            p1.stack.pop_back();
            p2.stack.pop_back();
            onTable += 4;
            toAppend += p1.getName() + " played " + p1Card.toString() + ". ";
            toAppend += p2.getName() + " played " + p2Card.toString() + ". ";
        }
        if(p1Card - p2Card > 0) {
            p1.addScore(onTable);
            toAppend += p1.getName() + " wins. ";
            p1Wins++;
        }
        else if(p1Card - p2Card < 0) {
            p2.addScore(onTable);
            toAppend += p2.getName() + " wins. ";
            p2Wins++;
        }
        log.push_back(toAppend);
        turns++;
        cout << "Turn " << to_string(turns) << " - " << toAppend << endl;
    }

    void Game::printLastTurn() {
        cout << log.back() << endl;
    }

    void Game::playAll() {
        while(!p1.stack.empty())
            playTurn();
    }

    void Game::printWiner() {
        if(p1.stack.empty())
            if(p1.cardesTaken() > p2.cardesTaken())
                cout << p1.getName() + " is the winner!";
            else if(p1.cardesTaken() < p2.cardesTaken())
                cout << p2.getName() + " is the winner!";
            else
                cout << " its a tie!";
        else
            cout << "Game is not over yet!";
            
    }

    void Game::printLog() {
        for(unsigned long i=0;i<log.size();i++) {
            cout << log[i] << endl;
        }
    }

    void Game::printStats() {
        double percent;
        int totalBattles = p1Wins + p2Wins + draws;

        cout << "Num of draws: " << draws << endl;
        percent = draws/totalBattles;
        cout << "Draw rate: " << to_string(percent) << endl;

        cout << p1.getName() << " statistics:" << endl;
        cout << "Cards taken: " << to_string(p1.cardesTaken()) << endl;
        percent = p1Wins/totalBattles;
        cout << "Winrate: " << to_string(percent) << endl;
         
        cout << p2.getName() << " statistics:" << endl;
        cout << "Cards taken: " << to_string(p2.cardesTaken()) << endl;
        percent = p2Wins/totalBattles;
        cout << "Winrate: " << to_string(percent) << endl;

    }
}