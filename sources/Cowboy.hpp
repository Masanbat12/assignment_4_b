#include "Character.hpp"    
#ifndef COWBOY_HPP
#define COWBOY_HPP

namespace ariel{
    class Cowboy:public Character{
        private:
            int bullets;
        public:
            Cowboy(std::string name, Point position);
            void shoot(Character*);
            bool hasboolets();
            int getBullets()
            {
                return bullets;
            }
            void reload();
            string print() override;
            
    };
}
#endif