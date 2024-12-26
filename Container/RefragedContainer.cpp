#include "RefragedContainer.hpp"


RefragedContainer::RefragedContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass, double maxT){
    this->number = number;
    this->client = client;
    this->length = length;
    this->width = width;
    this->height = height;
    this->cost = cost;
    this->mass = mass;
    this->maxTemperature = maxT;
}
    
int RefragedContainer::getLength() const {
    return length;
}

int RefragedContainer::getWidth() const{
    return width;
}

int RefragedContainer::getHeight() const {
    return height;
}

std::string RefragedContainer::getId() const {
    return number;
}
    
void RefragedContainer::setId(int X, int Y, int Z) {
    number = std::to_string(X) + "_" + std::to_string(Y) + "_" + std::to_string(Z);
}
    
std::string RefragedContainer::getClient() const {
    return client;
}

double RefragedContainer::getMass() const {
    return mass;
}
   
void RefragedContainer::getInfo(std::ostream& output) const {
    output << "Container ID: " << number << std::endl;
    output << "Client: " << client << std::endl;
    output << "Dimensions: " << length << "x" << width << "x" << height << std::endl;
    output << "Cost: $" << cost << std::endl;
    output << "Mass: " << mass << " kg" << std::endl;
    output << "MaxTemperature: " << maxTemperature << std::endl;
}

std::string RefragedContainer::isType() const  { return "Refraged";}

double RefragedContainer::getMaxTemperature() const {
    return maxTemperature;
}
   
std::shared_ptr<IContainer> RefragedContainer::Clone(size_t i, size_t method)  {
    switch (method)
    {
    case 0:
        return std::make_shared<RefragedContainer>(number, client, length, width, height, cost, mass, maxTemperature);
    case 1:
        return std::make_shared<RefragedContainer>(number, client, width, length, height, cost, mass, maxTemperature);
    case 2:
        return std::make_shared<RefragedContainer>(number, client, length, height, width, cost, mass, maxTemperature);
    case 3:
        return std::make_shared<RefragedContainer>(number, client, height, length, width, cost, mass, maxTemperature);
    case 4:
        return std::make_shared<RefragedContainer>(number, client, width, height, length, cost, mass, maxTemperature);
    case 5:
        return std::make_shared<RefragedContainer>(number, client, height, width, length, cost, mass, maxTemperature);
    default:
        return std::make_shared<RefragedContainer>(number, client, length, width, height, cost, mass, maxTemperature);
    }
}

bool RefragedContainer::operator==(const RefragedContainer& other) const {
    return number == other.number;
}

extern "C" IContainer* createRefrigeratedContainer(std::string id, std::string cl_nt, int l, int w, int h, double newcost, double mass, double maxP, double maxT) {
    return new RefragedContainer(id, cl_nt, l, w, h, newcost, mass, maxT);
}

void RefragedContainer::setId(const std::string& newId)  { number = newId; }

void RefragedContainer::setClient(const std::string& newClient) { client = newClient; }

void RefragedContainer::setDimensions(int len, int w, int h) { length = len; width = w; height = h; }

void RefragedContainer::setCost(double newCost) { cost = newCost; }

void RefragedContainer::setMass(double newMass) { mass = newMass; }

void RefragedContainer::setMaxTemperature(double Temperature) { maxTemperature = Temperature; }