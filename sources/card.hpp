#pragma once

using namespace std;

namespace ariel {
    class card {
    private:
        int num, type;

    public:
        //inline
        card(int num, int type) {
            this->num = num; 
            this->type=type;
        }

        int getNum() const {return num;}

        friend bool operator- (const card& c1, const card& c2) {
            return (c1.getNum()) - (c2.getNum());
        }

        //outline
        friend ostream& operator<< (ostream& output, const card& c);
        string toString();
    };
}