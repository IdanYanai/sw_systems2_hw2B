#include <string>
#include <vector>

using namespace std;

#include "card.hpp"

#ifndef PLAYER
#define PLAYER

namespace ariel {
    class Player {
        private:
            string name;
            int score; // cards taken
            bool inGame;
            vector<card> stack;

        public:

            Player() : name("Idan"), score(0), inGame(false) {}
            Player(string name) : name(move(name)), score(0), inGame(false) {}
            void addScore(int toAdd) {this->score += toAdd;}

            int stacksize() const { return int(stack.size()); }
            int cardesTaken() const {return this->score; }
            bool isInGame() const {return this->inGame;}
            void setInGame(bool status) {this->inGame = status;}
            string getName() { return this->name; } 

            friend ostream& operator<< (ostream& output, const Player& playa) {
                output << playa.name << flush;
                return output;
            }

            void drawCard(card& cardo) {
                stack.push_back(cardo);
            }

            card& playCard() {
                card& toReturn = stack.back();
                stack.pop_back();
                return toReturn;
            }
    };
}

#endif