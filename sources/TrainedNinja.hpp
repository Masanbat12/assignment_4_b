#include "Ninja.hpp"
#ifndef TRAINEDNINJA_HPP
#define TRAINEDNINJA_HPP

namespace ariel
{
    class TrainedNinja : public Ninja
    {
        public:
            TrainedNinja(string _name, Point locat):Ninja(_name,locat,120,12){};

    };
}
#endif