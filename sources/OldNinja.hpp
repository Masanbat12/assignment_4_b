
#include "Ninja.hpp"
#ifndef OLDNINJA_HPP
#define OLDNINJA_HPP
namespace ariel
{
    class OldNinja : public Ninja
    {
        public:
            OldNinja(string _name, Point locat):Ninja(_name,locat,150,8){};
    };
}
#endif