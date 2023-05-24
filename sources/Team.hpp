#pragma once
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include "Character.hpp"
#include <vector>


namespace ariel
{
    class Team
    {
        private:
            vector<Cowboy*> cowboys;
            vector<Ninja*> ninjas;
            Character* leader_t;
        protected:
            Character* getTeamLeader() const {
                return leader_t;
            }
            void setTeamLeader(Character* new_l) {
                leader_t = new_l;
            }
        public:
            Team(Character*);
            Team();
            virtual void attack(Team* other);
            virtual string print();
            virtual void add(Character* Character);
            virtual int stillAlive();
            virtual Character* getClosest(Point p);
            
            
            virtual ~Team() = default;
            Team(const Team&) = default;
            Team& operator=(const Team&) = default;
            Team(Team&&) = default;
            Team& operator=(Team&&) = default;
    };
}