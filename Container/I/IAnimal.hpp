#ifndef IANIMAL_HPP
#define IANIMAL_HPP
#include "IContainer.hpp"

struct Animal;

class IAnimalContainer : virtual public IContainer{
    public:
        virtual void setAnimal(const Animal& animal) = 0;
        virtual Animal getAnimal() const = 0;
}; 

#endif