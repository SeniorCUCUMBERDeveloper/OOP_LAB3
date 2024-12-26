#ifndef EXPLOSIVECONTAINER_HPP
#define EXPLOSIVECONTAINERCONTAINER_HPP


#include "./Container.hpp"


class ExplosiveContainer : public Container{
    public:
        ExplosiveContainer();

        ExplosiveContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass);

        ~ExplosiveContainer() override {}

        std::string isType() const override;
};





#endif