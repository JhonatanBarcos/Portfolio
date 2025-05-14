
#ifndef _MATCH_
#define _MATCH_

#include "Player.hpp"
#include "Team.hpp"

class Match {

private:

    Team * teamOne;
    Team * teamTwo;
    int goalOne;
    int goalTwo;
    std::list<Player *> scorersOne;
    std::list<Player *> scorersTwo;

    void simulateScorers(Team * t, std::list<Player *> & l, int g) {
        for (int i = 0; i < g; ++i) {
            int ix = rand() % t->getPlayers().size();
            std::list<Player *>::iterator it = t->getPlayers().begin();
            std::advance(it, ix);
            l.push_back(*it);
        }
    }
	
public:

	Match(Team * o, Team * t) {
		teamOne = o;
		teamTwo = t;
	}
	
	Team * getTeamOne() {
        return teamOne;
    }

    Team * getTeamTwo() {
        return teamTwo;
    }

    int getGoalOne() {
        return goalOne;
    }

    int getGoalTwo() {
        return goalTwo;
    }

    std::list<Player *> & getScorersOne() {
        return scorersOne;
    }

    std::list<Player *> & getScorersTwo() {
        return scorersTwo;
    }

    void simulateMatch() {
        goalOne = rand() % 6;
        goalTwo = rand() % 6;
        simulateScorers(teamOne, scorersOne, goalOne);
        simulateScorers(teamTwo, scorersTwo, goalTwo);
    }

    void printMatch() {
        std::cout << teamOne->getName() + "-" + teamTwo->getName() + ": ";
        std::cout << goalOne << "-" << goalTwo << "\n";
    }
    
};

#endif

