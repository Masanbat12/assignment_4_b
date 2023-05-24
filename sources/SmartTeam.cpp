#include "SmartTeam.hpp"
#include "Team.hpp"
#include <stdexcept>

namespace ariel
{
    SmartTeam::SmartTeam(Character* player1) : Team(player1)
    {
        this->add(player1);
    }

    void SmartTeam::attack(Team* enemyTeam)
    {
        if (enemyTeam == nullptr)
        {
            throw std::invalid_argument("Enemy team is null or dead");
        }

        if (enemyTeam->stillAlive() == 0)
        {
            throw std::runtime_error("No living defenders left");
        }
        if (this->stillAlive() == 0)
        {
            throw std::runtime_error("Attacking team is not alive");
        }
        if (enemyTeam->stillAlive() == 0 && this->stillAlive() == 0)
        {
            throw std::runtime_error("Both teams have died");
        }
        if (this == enemyTeam)
        {
            throw std::runtime_error("Cannot harm self");
        }

        // Check if the leader of the attacking team is alive
        if (!getTeamLeader()->isAlive())
        {
            // Find the nearest living figure as the new leader
            Character* newLeader = getClosest(getTeamLeader()->getLocation());
            if (newLeader == nullptr)
            {
                throw std::runtime_error("No living figures in the attacking group to choose a new leader");
            }
            setTeamLeader(newLeader);
        }

        Character* victim = enemyTeam->getClosest(getTeamLeader()->getLocation());
        if (victim == nullptr)
        {
            throw std::runtime_error("No living figures in the enemy group to choose a victim");
        }

        // Perform the attack
        for (Character* character : getTeamates())
        {
            if (!character->isAlive())
            {
                continue;
            }

            if (!victim->isAlive())
            {
                victim = enemyTeam->getClosest(getTeamLeader()->getLocation());
                if (!victim)
                {
                    return;
                }
            }

            if (Cowboy* cowboy = dynamic_cast<Cowboy*>(character))
            {
                if (cowboy->hasboolets())
                {
                    cowboy->shoot(victim);
                }
                else
                {
                    cowboy->reload();
                }
            }
            else if (Ninja* ninja = dynamic_cast<Ninja*>(character))
            {
                if (ninja->distance(victim) <= 1.0)
                {
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
