#include "Frag_and_Ref.hpp"


FragileRefragedContainer::FragileRefragedContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass, double maxM, double maxT){
    this->number = number;
    this->client = client;
    this->length = length;
    this->width = width;
    this->height = height;
    this->cost = cost;
    this->mass = mass;
    this->maxPressure = maxM;
    this->maxTemperature = maxT;
}

std::string FragileRefragedContainer::isType() const { return "Fragile and Refraged Container";}

int FragileRefragedContainer::getLength() const {
    return length;
}
    
int FragileRefragedContainer::getWidth() const {
    return width;
}

int FragileRefragedContainer::getHeight() const {
    return height;
}

std::string FragileRefragedContainer::getId() const {
    return number;
}

void FragileRefragedContainer::setId(int X, int Y, int Z) {
    number = std::to_string(X) + "_" + std::to_string(Y) + "_" + std::to_string(Z);
}

double FragileRefragedContainer::getMass() const {
    return mass;
}

std::string FragileRefragedContainer::getClient() const {
    return client;
}

void FragileRefragedContainer::getInfo(std::ostream& output) const {
    output << "Container ID: " << number << std::endl;
    output << "Client: " << client << std::endl;
    output << "Dimensions: " << length << "x" << width << "x" << height << std::endl;
    output << "Cost: $" << cost << std::endl;
    output << "Mass: " << mass << " kg" << std::endl;
    output << "MaxPressure: " << maxPressure << std::endl;
    output << "Max Temperature: " << maxTemperature << std::endl;
}

double FragileRefragedContainer::getMaxPressure() const { return maxPressure; }

double FragileRefragedContainer::getMaxTemperature() const { return maxTemperature; }

std::shared_ptr<IContainer> FragileRefragedContainer::Clone(size_t i, size_t method) { 
    switch (method)
    {
    case 0:
        return std::make_shared<FragileRefragedContainer>(number, client, length, width, height, cost, mass,  maxPressure, maxTemperature);
    case 1:
        return std::make_shared<FragileRefragedContainer>(number, client, width, length, height, cost, mass,  maxPressure, maxTemperature);
    case 2:
        return std::make_shared<FragileRefragedContainer>(number, client, length, height, width, cost, mass,  maxPressure, maxTemperature);
    case 3:
        return std::make_shared<FragileRefragedContainer>(number, client, height, length, width, cost, mass,  maxPressure, maxTemperature);
    case 4:
        return std::make_shared<FragileRefragedContainer>(number, client, width, height, length, cost, mass,  maxPressure, maxTemperature);
    case 5:
        return std::make_shared<FragileRefragedContainer>(number, client, height, width, length, cost, mass,  maxPressure, maxTemperature);
    default:
        return std::make_shared<FragileRefragedContainer>(number, client, length, width, height, cost, mass,  maxPressure, maxTemperature);
    }
}
    
bool FragileRefragedContainer::operator==(const FragileRefragedContainer& other) const {
    return number == other.number;
}

extern "C" IContainer* createFragileRefrigeratedContainer(std::string id, std::string cl_nt, int l, int w, int h, double newcost, double mass, double maxP, double maxT) {
    return new FragileRefragedContainer(id, cl_nt, l, w, h, newcost, mass, maxP, maxT);
}

void FragileRefragedContainer::setId(const std::string& newId) { number = newId; }

void FragileRefragedContainer::setClient(const std::string& newClient) { client = newClient; }

void FragileRefragedContainer::setDimensions(int len, int w, int h) { length = len; width = w; height = h; }

void FragileRefragedContainer::setCost(double newCost) { cost = newCost; }

void FragileRefragedContainer::setMass(double newMass) { mass = newMass; }

void FragileRefragedContainer::setMaxPressure(double Pressure) { maxPressure = Pressure; }

void FragileRefragedContainer::setMaxTemperature(double Temperature) { maxTemperature = Temperature; }