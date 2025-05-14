#ifndef _GOALKEEPER_
#define _GOALKEEPER_

#include "Player.hpp"
#include "Match.hpp"

class Goalkeeper : public Player{

    private:
        int noSaves;
        int noGoalsLet;
    
    public:
        Goalkeeper(bool i, std::string n, int a, Country * c) : Player(i, n, a, c){
            noSaves = 0;
            noGoalsLet = 0;
        }

        void updateStats(Match * m){
            noSaves += rand() % 10;
            noGoalsLet += rand() % 10;
        }

        void printStats(){
            std::cout << "\n* Printing stats of " << name << std::endl;
            std::cout << "Saves: " << noSaves << std::endl;
            std::cout << "Goals let: " << noGoalsLet << std::endl;
        }

};

#endif
