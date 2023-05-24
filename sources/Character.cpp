#include "Character.hpp"
#include <math.h>
#include <string>

namespace ariel{
    Character::Character(string _name, Point location, int health):name(_name), place(location), life(health),
    inside(false){}

    bool Character::isAlive()
    {
        return life > 0;
    }

    double Character::distance(Character* other_char)
    {
        /* Calculate the Euclidean distance between the current character's
            location and the other character's location */ 
        return place.distance(other_char->place);
    }

    void Character::hit(int dam)
    {
        if (dam <= 0){
            throw invalid_argument("damage is negative");
        }
        life -= dam;
        if (life < 0) 
        {
            life = 0;
        }
    }
//     void Character::move2(Point newLocation) {
//     place = newLocation;
// }
    /* print not implemanted in here because its override by the other classs */
}

            