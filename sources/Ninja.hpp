#include "Character.hpp"
#include <stdexcept>
#ifndef NINJA_HPP
#define NINJA_HPP

namespace ariel
{
    class Ninja: public Character
    {
        private:
            int speed;
        public:
            Ninja(string _name, Point location, int health, int _speed);
            void slash(Character* enemy);
            void move(Character* enemy);
            int g_Speed();
            void setLoc(Point Location)
            {
            setLoc(Location);
            }
            string print();
            
    };
}
#endif