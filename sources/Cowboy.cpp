#include "Cowboy.hpp"
#include <stdexcept>

namespace ariel{
    
    Cowboy::Cowboy(string name, Point position):Character(name,position,110), bullets(6){}

    void Cowboy::shoot(Character *enemy)
    {
            if(!this->isAlive())
            {
                throw std::runtime_error("2)Dead characters cannot attack and characters cannot attack a dead enemy");
            }
            if (this->getBullets() == 0) {
                //throw std::runtime_error("No bullets left!");
                return;
            }
            if (enemy == nullptr) {
                throw std::invalid_argument("Invalid enemy pointer!");
            }
            if (!enemy->isAlive())
            {
                throw std::runtime_error("1) Dead characters cannot attack and characters cannot attack a dead enemy");
            }
           
            if (enemy == this)
            {
                throw std::runtime_error("No self harm");
            }
            enemy->hit(10);
            --bullets;
    }

    bool Cowboy::hasboolets()
    {
        if(getBullets() > 0)
        {
            return true;
        }
        else
            return false;
    }

    void Cowboy::reload()
    {
        if (!this->isAlive()){
            throw std::runtime_error("dead cowboy can't reload");
        }
        else{
                bullets = 6;
        }
    }

    string Cowboy::print()
    {
       /* Return a string representation of the cowboy's information */
        return "Name: " + getName() + ", Location: (" + to_string(getLocation().get_X()) +
            ", " + to_string(getLocation().get_Y()) + "), Health: " + to_string(getLife()) +
            ", Bullets: " + to_string(bullets);
    }
}