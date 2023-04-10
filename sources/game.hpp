#include "player.hpp"
#include <string>
#include <vector>

using namespace std;

namespace ariel {
    class Game {
    private:
        Player& p1, p2;
        vector<string> log;
        int turns, p1Wins, p2Wins, draws;

    public:
        Game(Player& p1to, Player& p2to);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();

        int getTurns() const { return turns; }
        void incrementTurns() { turns++; }
        int getp1Wins() const { return p1Wins; }
        void incrementp1Wins() { p1Wins++; }
        int getp2Wins() const { return p2Wins; }
        void incrementp2Wins() { p2Wins++; }
        int getDraws() const { return draws; }
        void incrementDraws() { draws++; }
    };
}