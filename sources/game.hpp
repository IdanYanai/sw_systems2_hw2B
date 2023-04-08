#include "player.hpp"
#include <string>
#include <vector>

using namespace std;

namespace ariel {
    class Game {
    private:
        Player p1, p2;
        vector<string> log;

    public:
        int turns, p1Wins, p2Wins, draws;
        Game(Player& p1to, Player& p2to);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
}