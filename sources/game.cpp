#include "player.hpp"
#include "card.hpp"
#include "game.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

namespace ariel {
    Game::Game(Player& p1, Player& p2) {
        this->p1 = p1;
        this->p2 = p2;

        turns=0;
        p1Wins=0;
        p2Wins=0;
        draws=0;

        vector<card> fullStack;
        for(int i=0;i<4;i++)
            for(int j=0;j<13;j++)
                fullStack.push_back(card(j,i));
        
        int random;
        for(int i=0;i<26;i++) {
            srand((unsigned) time(NULL));
            random = rand() % fullStack.size();
            p1.stack.push_back(fullStack[random]);
            fullStack.erase(fullStack.begin() + random);
        }

        for(int i=0;i<26;i++) {
            p2.stack.push_back(fullStack.back());
            fullStack.pop_back();
        }
    }

    void Game::playTurn() {
        if(p1.stack.size() == 0)
            cout << "Game already finished" << endl;

        string toAppend = "";
        card p1Card = p1.stack.back();
        card p2Card = p2.stack.back();
        p1.stack.pop_back();
        p2.stack.pop_back();
        int onTable = 2;
        toAppend += p1.getName() + " played " + p1Card.toString() + ". ";

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
            toAppend += p1.getName() + " played " + p1Card.toString();
        }
        if(p1Card - p2Card > 0) {
            p1.addScore(onTable);
            toAppend += p1.getName() + " wins. ";
            p1Wins++;
        }
        else if(p1Card - p2Card < 0) {
            p2.addScore(onTable);
            toAppend += p1.getName() + " wins. ";
            p2Wins++;
        }
        log.push_back(toAppend);
        turns++;
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
        for(int i=0;i<log.size();i++) {
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