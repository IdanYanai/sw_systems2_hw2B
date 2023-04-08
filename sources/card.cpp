#include "card.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace ariel {
    ostream& operator<< (ostream& output, const card& c) {
        string sType;
        if(c.type == 0)
            sType = " of Clubs";
        else if(c.type == 1)
            sType = " of Diamonds";
        else if(c.type == 2)
            sType = " of Hearts";
        else if(c.type == 3)
            sType = " of Spades";

        if(c.num == 10)
            output << "Jack " << sType;    
        else if(c.num == 11)
            output << "Queen " << sType;
        else if(c.num == 12)
            output << "King " << sType;
        else if(c.num == 1)
            output << "Ace " << sType;
        else
            output << to_string(c.num) << ' ' << sType;

        return output;
    }

    string card::toString() {
        string sType;
        if(type == 0)
            sType = " of Clubs";
        else if(type == 1)
            sType = " of Diamonds";
        else if(type == 2)
            sType = " of Hearts";
        else if(type == 3)
            sType = " of Spades";

        string desc;
        if(num == 10)
            desc = "Jack" + sType;    
        else if(num == 11)
            desc = "Queen" + sType;
        else if(num == 12)
            desc = "King" + sType;
        else if(num == 1)
            desc = "Ace" + sType;
        else
            desc = to_string(num) + ' ' + sType;

        return desc;
    }
}