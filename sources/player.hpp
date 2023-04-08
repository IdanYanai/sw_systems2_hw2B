#include <string>
#include <vector>
#include "card.hpp"

#ifndef PLAYER
#define PLAYER

using namespace std;

namespace ariel {
    class Player {
        private:
            string name;
            int score; // cards taken
            bool inGame;

        public:
            vector<card> stack;

            Player() {
                this->name = "Idan"; 
                this->score = 0; 
                this->inGame = false;
            }
            Player(string name) {this->name = name; }
            int addScore(int toAdd) {this->score += toAdd;}

            int stacksize() { return stack.size(); }
            int cardesTaken() {return this->score; }
            bool isInGame() {return this->inGame;}
            void setInGame(bool status) {this->inGame = status;}
            string getName() {return this->name;}
    };
}

#endif