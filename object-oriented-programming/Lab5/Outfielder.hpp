#ifndef _OUTFIELDER_
#define _OUTFIELDER_

#include "Player.hpp"
#include "Match.hpp"

class Outfielder : public Player{

    private:
        int noTrackles;
        int noPasses;
        int noShots;
        int noAssists;
        int noGoals;
    
    public:
        Outfielder(bool i, std::string n, int a, Country * c) : Player(i, n, a, c){
            noTrackles = 0;
            noPasses = 0;
            noShots = 0;
            noAssists = 0;
            noGoals = 0;
        }

        void updateStats(Match * m){
            noTrackles += rand() % 10;
            noPasses += rand() % 10;
            noShots += rand() % 10;
            noAssists += rand() % 10;
            noGoals += rand() % 10;
        }

        void printStats(){
            std::cout << "\n* Printing stats of " << name << std::endl;
            std::cout << "Trackles: " << noTrackles << std::endl;
            std::cout << "Passes: " << noPasses << std::endl;
            std::cout << "Shots: " << noShots << std::endl;
            std::cout << "Assists: " << noAssists << std::endl;
            std::cout << "Goals: " << noGoals << std::endl;
        }

};

#endif
