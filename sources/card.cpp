#include <string>
#include <iostream>

using namespace std;

#include "card.hpp"

namespace ariel {
    card::card(int num, int type) : num(num), type(type) {}

    ostream& operator<< (ostream& output, const card& cardo) {
        string sType;
        if(cardo.type == 0)
            sType = " of Clubs";
        else if(cardo.type == 1)
            sType = " of Diamonds";
        else if(cardo.type == 2)
            sType = " of Hearts";
        else if(cardo.type == 3)
            sType = " of Spades";

        if(cardo.num == 11)
            output << "Jack" << sType;    
        else if(cardo.num == 12)
            output << "Queen" << sType;
        else if(cardo.num == 13)
            output << "King" << sType;
        else if(cardo.num == 1)
            output << "Ace" << sType;
        else
            output << to_string(cardo.num) << sType << flush;

        return output;
    }

    string card::toString() {
        string sType;
        if(type == 0)
            sType = string(" of Clubs");
        else if(type == 1)
            sType = string(" of Diamonds");
        else if(type == 2)
            sType = string(" of Hearts");
        else if(type == 3)
            sType = string(" of Spades");

        string desc;
        if(num == 11)
            desc = string("Jack") + sType;    
        else if(num == 12)
            desc = string("Queen") + sType;
        else if(num == 13)
            desc = string("King") + sType;
        else if(num == 1)
            desc = string("Ace") + sType;
        else
            desc = to_string(num) + sType;
        
        return desc;
    }
}