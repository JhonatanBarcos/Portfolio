#ifndef _PLAYER_
#define _PLAYER_

#include "Country.hpp"
class Team;
class Match;

class Player{

    protected:
        bool _isFemale;
        std::string name;
        int age;
        Country * nacionality;
        int noMatches;

    public:
        Player(bool i, std::string n, int a, Country * c){
            _isFemale = i;
            name = n;
            age = a;
            nacionality = c;
        }

        bool isFemale() const{
            return _isFemale;
        }

        std::string getName(){
            return name;
        }

        int getAge(){
            return age;
        }

        Country * getNacionality(){
            return nacionality;
        }

        int getNoMatches(){
            return noMatches;
        }

        virtual void updateStats(Match * m) = 0;
        virtual void printStats() = 0;


};


#endif