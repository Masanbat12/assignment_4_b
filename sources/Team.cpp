#include "Team.hpp"
#include <iostream>
#include <limits>



namespace ariel
{
    Team::Team(): leader_t(nullptr)
        {}

    Team::Team(Character *cha): leader_t(cha)
        {
            this->add(cha);
        }


    void Team::add(Character *player)
    {
        if (player == nullptr) {
        throw std::invalid_argument("Invalid player: nullptr");
        }
        if (cowboys.size() + ninjas.size() >= 10){
            throw std::runtime_error("the team is full");
        }
        if (player->getInside()){
            throw std::runtime_error("already in a team");
        }
        player->setInside(true);
        Cowboy* cowboy = dynamic_cast<Cowboy*>(player);
        if (cowboy != nullptr)
        {
            cowboys.push_back(cowboy);
            return;
        }

        Ninja* ninja = dynamic_cast<Ninja*>(player);
        if (ninja != nullptr)
        {
            ninjas.push_back(ninja);
            return;
        }

        throw std::invalid_argument("Invalid character type. Only Cowboys and Ninjas are allowed in the team.");
    }

Character* Team::getClosest(Point loc){
    Character* newLeader = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (Cowboy* cowboy : cowboys){
        if (cowboy->isAlive()){
            double distance = cowboy->getLocation().distance(loc);
            if (distance < minDistance){
                newLeader = cowboy;
                minDistance = distance;
            }
        }
    }

    for (Ninja* ninja : ninjas){
        if (ninja->isAlive()){
            double distance = ninja->getLocation().distance(loc);
            if (distance < minDistance)
            {
                newLeader = ninja;
                minDistance = distance;
            }
        }
    }
    /* If no living figures found,
       take alternative action (e.g., return the team leader) */
    if (newLeader == nullptr){
        newLeader = getTeamLeader();
    }
    return newLeader;
}


    
    void Team::attack(Team* enemyTeam){
    if(enemyTeam == nullptr){
        throw std::invalid_argument("team is null or dead");
    }
    
    if(enemyTeam->stillAlive() == 0){
        throw std::runtime_error("No living defender left");
    }
    if (this->stillAlive() == 0) {
        throw std::runtime_error("Attacking team is not alive");
    }
    if((enemyTeam->stillAlive() == 0) && (this->stillAlive() == 0))
    {
        throw std::runtime_error("1) Both teams died");
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
        if (newLeader == nullptr)
        {
            throw std::runtime_error("No living figures in the attacking group to choose a new leader.");
            // return;
        }
    }
    Character* victim = enemyTeam->getClosest(getTeamLeader()->getLocation());
    if (victim == nullptr) {
    /*No living figures in the enemy group,
      do something (e.g., return or continue the battle) */
        throw std::runtime_error("No living figures in the enemy group to choose a victim.");
    }
    // Perform the attack
    for (Cowboy* cowboy : cowboys)
    {
        if (cowboy != nullptr && cowboy->isAlive())
        {
            if (cowboy->hasboolets())
            {
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
    }

    for (Ninja* ninja : ninjas)
    {
        if (ninja != nullptr && ninja->isAlive())
        {
            double distanceToVictim = ninja->getLocation().distance(victim->getLocation());
            if (distanceToVictim < 1.0)
            {
                if (!victim->isAlive() && victim != nullptr){
                    victim = enemyTeam->getClosest(getTeamLeader()->getLocation());
                    if (victim == nullptr)
                    {
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


         int Team::stillAlive()
        {
            int team_Number = 0;

           for (size_t i = 0; i < ninjas.size(); i++)
           {
                if(ninjas[i]->isAlive())
                {
                    team_Number++;
                }
           }
           for (size_t j = 0; j < cowboys.size(); j++)
           {
                if(cowboys[j]->isAlive())
                { 
                    team_Number++;
                }
           }
           return team_Number;
        }

        string Team::print()
        {
            string output = "";
            for (size_t m = 0; m < ninjas.size(); m++)
            {
                output += ninjas[m]->print();
            }
            for (size_t k = 0; k < cowboys.size(); k++)
            {
                output += cowboys[k]->print(); 
            } 
            return output;
        } 
}