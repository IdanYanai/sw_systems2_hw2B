#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace ariel {
    class card {
    private:
        int num, type;

    public:
        //inline
        card() : num(0), type(0) {}

        int getNum() const {return num;}
        int getType() const {return type;}

        friend int operator- (const card& card1, const card& card2) {
            return (card1.getNum()) - (card2.getNum());
        }

        // void operator= (const card& cardio) { this->num = cardio.num; }

        //outline
        card(int, int);
        friend ostream& operator<< (ostream& output, const card& cardo);
        string toString();
    };
}