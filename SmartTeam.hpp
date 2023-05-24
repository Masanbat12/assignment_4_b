#include "Team.hpp"
#include <vector>



namespace ariel
{
    class SmartTeam:public virtual Team
    {
        public:
            SmartTeam(Character*);
            void attack(Team *enemy) override;            
    };
}