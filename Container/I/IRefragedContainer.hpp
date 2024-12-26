#ifndef IREFRAGEDCONTAINER_HPP
#define IREFRAGEDCONTAINER_HPP


#include "IContainer.hpp"

class IRefragedContainer : virtual public IContainer{
    public:
        virtual double getMaxTemperature() const = 0;
        virtual void setMaxTemperature(double Temperature) = 0;
};

#endif