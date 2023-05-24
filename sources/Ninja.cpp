#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include <stdexcept>



namespace ariel
{
    Ninja::Ninja(string _name, Point location, int health, int _speed):Character(_name,location,health)
                                                                       ,speed(_speed){};
    void Ninja::slash(Character* enemy)
    {
        if (enemy == nullptr)
        {
            throw std::invalid_argument("Invalid enemy character");
        }
        if (!this->isAlive())
        {
            throw std::runtime_error("4)Dead characters cannot attack and characters cannot attack a dead enemy");
        }
        if (!enemy->isAlive())
        {
            throw std::runtime_error("3)Dead characters cannot attack and characters cannot attack a dead enemy");
        }
        
        if (enemy == this)
        {
            throw std::runtime_error("No self harm");
        }
        double dst = getLocation().distance(enemy->getLocation());
        if (dst < 1.0){
            enemy->hit(40);
        }
    }
    
    void Ninja::move(Character* enemy)
    {
        if (!enemy)
        {
            throw std::invalid_argument("Invalid enemy character");
        }
        if (!isAlive()) {
        throw std::runtime_error("Cannot move. Ninja is dead.");
        }
        if(this->isAlive())
        {
            Point beginning = this->getLocation();
            Point e_loc = enemy->getLocation();

            this->place = Point::moveTowards(place, e_loc, g_Speed());
        }
    }

    int Ninja::g_Speed()
    {
        return this->speed;
    }
    
    // printing
    string Ninja::print()
    {
        /* Return a string representation of the young ninja's information */
        return "Name: " + getName() + ", Location: (" + to_string(getLocation().get_X()) +
            ", " + to_string(getLocation().get_Y()) + "), Health: " + to_string(getLife()) +
            ", Speed: " + to_string(g_Speed());
    }
}