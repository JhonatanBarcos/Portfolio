
#ifndef _MAIN_
#define _MAIN_

#include "Goalkeeper.hpp"
#include "Outfielder.hpp"


int main() {
    // Create countries
    Country * c1 = new Country("Portugal");
    Country * c2 = new Country("Spain");

    // Create outfielders from different countries
    Player * o1 = new Outfielder(false, "Cristiano Ronaldo", 35, c1);
    Player * o2 = new Outfielder(false, "Bernardo Silva", 26, c1);
    Player * o3 = new Outfielder(false, "Sergio Ramos", 34, c2);
    Player * o4 = new Outfielder(false, "Sergio Busquets", 32, c2);

    //Create two teams with the outfielders
    Team * team1 = new Team("Portugal Male Team", c1, Team::Gender::MALE);
    team1->addPlayer(o1);
    team1->addPlayer(o2);

    Team * team2 = new Team("Spain Male Team", c2, Team::Gender::MALE);
    team2->addPlayer(o3);
    team2->addPlayer(o4);

    //Create a match between two teams
    Match * m = new Match(team1, team2);

    //Simulate match
    std::cout << "\nSimulating match..." << std::endl;
    m->simulateMatch();

    //Print match stats
    std::cout << "\nPrinting match..." << std::endl;
    m->printMatch();


    //Update stats of each player
    std::cout << "\nUpdating stats..." << std::endl;
    o1->updateStats(m);
    o2->updateStats(m);
    o3->updateStats(m);
    o4->updateStats(m);

    //Print stats of each player
    std::cout << "\nPrinting stats..." << std::endl;
    o1->printStats();
    o2->printStats();
    o3->printStats();
    o4->printStats();


};

#endif