#include "Team2.hpp"
#include "Team.hpp"
#include <iostream>
#include <cmath>
#include <limits>



namespace ariel
{ 
Team2::Team2(Character *cha) {
            setTeamLeader(cha);
            this->add(cha);
        }


    void Team2::add(Character *player)
    {
        if (player == nullptr) {
        throw std::invalid_argument("Invalid player: nullptr");
        }
        if (teamates.size() >= 10){
            throw std::runtime_error("the team is full");
        }
        if (player->getInside()){
            throw std::runtime_error("already in a team");
        }
        
        player->setInside(true);
       teamates.push_back(player);
    }

Character* Team2::getClosest(Point loc)
{
    Character* newLeader = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (Character* character : teamates)
    {
        if (character->isAlive())
        {
            double distance = character->getLocation().distance(loc);
            if (distance < minDistance)
            {
                newLeader = character;
                minDistance = distance;
            }
        }
    }

    // If no living figures found, take alternative action (e.g., return the team leader)
    if (newLeader == nullptr)
    {
        newLeader = getTeamLeader();
    }

    return newLeader;
}


    void Team2::attack(Team* enemyTeam)
    {
    if (!enemyTeam){
        throw std::invalid_argument("Invalid enemy team");
    }
    if(enemyTeam->stillAlive() == 0){
        throw std::runtime_error("No living enemy left");
    }
    if (this->stillAlive() == 0) {
        throw std::runtime_error("Attacking team is not alive");
    }
    if((enemyTeam->stillAlive() == 0) && (this->stillAlive() == 0))
    {
        throw std::runtime_error("2) Both teams died");
    }
    if(this == enemyTeam)
    {
        throw std::runtime_error("No harm self");
    }
    // Check if the leader of the attacking group is alive
    if (!getTeamLeader()->isAlive())
    {
        // getTeamLeader()->move2(enemyTeam->getTeamLeader()->getLocation()); // Replace 'someNewLocation' with the desired new location
        // Find the nearest living figure as the new leader
    Character* newLeader = getClosest(getTeamLeader()->getLocation());
    setTeamLeader(newLeader);
        if (newLeader == nullptr){
        throw std::runtime_error("No living figures in the attacking group to choose a new leader.");
        }
    }
    Character* victim = enemyTeam->getClosest(getTeamLeader()->getLocation());
    if (victim == nullptr)
    {
        throw std::runtime_error("No living figures in the enemy group to choose a victim.");
    }
    // Perform the attack
    for (Character* character : teamates)
    {
        if (character->isAlive())
        {
            Cowboy* cowboy = dynamic_cast<Cowboy*>(character);
            Ninja* ninja = dynamic_cast<Ninja*>(character);
            if (cowboy != nullptr && cowboy->isAlive()){
                if (cowboy->hasboolets()){
                    if (!victim->isAlive() && victim != nullptr){
                        victim = enemyTeam->getClosest(getTeamLeader()->getLocation());
                        if (victim == nullptr) {
                        /*No living figures in the enemy group,
                          do something (e.g., return or continue the battle) */
                            throw std::runtime_error("No living figures in the enemy group to choose a victim.");
                            }
                    }
                 cowboy->shoot(victim);
                }
                else
                {
                    cowboy->reload();
                }
            }
            else if (ninja != nullptr  && ninja->isAlive()){
            double distanceToVictim = ninja->getLocation().distance(victim->getLocation());
                if (distanceToVictim <= 1.0)
                {
                    if (!victim->isAlive() && victim != nullptr){
                        victim = enemyTeam->getClosest(getTeamLeader()->getLocation());
                    if (victim == nullptr) {
                        /*No living figures in the enemy group,
                          do something (e.g., return or continue the battle) */
                        throw std::runtime_error("No living figures in the enemy group to choose a victim.");
                        }
                    }
                ninja->slash(victim);
                }
                else
                {
                    ninja->move(victim);
                }
            }
        }
    }
}


         int Team2::stillAlive()
        {
            int team_Number = 0;

           for (size_t i = 0; i < teamates.size(); i++)
           {
                if(teamates[i]->isAlive())
                {
                    team_Number++;
                }
           }
           return team_Number;
        }

        string Team2::print()
        {
            string output = "";
            for (size_t m = 0; m < teamates.size(); m++)
            {
                output += teamates[m]->print();
            }
            return output;
        } 

}