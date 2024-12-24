#include "FragileContainer.hpp"


FragileContainer::FragileContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass,  double maxM){
    this->number = number;
    this->client = client;
    this->length = length;
    this->width = width;
    this->height = height;
    this->cost = cost;
    this->mass = mass;
    this->maxPressure = maxM;
}
    
std::string FragileContainer::getClient() const {
    return client;
}
    
int FragileContainer::getLength() const {
    return length;
}
    
int FragileContainer::getWidth() const{
    return width;
}
        
int FragileContainer::getHeight() const {
    return height;
}
        
std::string FragileContainer::getId() const{
    return number;
}
    
void FragileContainer::setId(int X, int Y, int Z) {
    number = std::to_string(X) + "_" + std::to_string(Y) + "_" + std::to_string(Z);
}
    
double FragileContainer::getMass() const {
    return mass;
}
       
void FragileContainer::getInfo(std::ostream& output) const {
    output << "Container ID: " << number << std::endl;
    output << "Client: " << client << std::endl;
    output << "Dimensions: " << length << "x" << width << "x" << height << std::endl;
    output << "Cost: $" << cost << std::endl;
    output << "Mass: " << mass << " kg" << std::endl;
    output << "MaxPressure: " << maxPressure << std::endl;
}
    
std::string FragileContainer::isType() const  { return "Fragile"; }
    
double FragileContainer::getMaxPressure() const { return maxPressure; }
        
std::shared_ptr<IContainer> FragileContainer::Clone(size_t i, size_t method)  { 
    switch (method)
    {
    case 0:
        return std::make_shared<FragileContainer>(number, client, length, width, height, cost, mass, maxPressure);
    case 1:
        return std::make_shared<FragileContainer>(number, client, width, length, height, cost, mass, maxPressure);
    case 2:
        return std::make_shared<FragileContainer>(number, client, length, height, width, cost, mass, maxPressure);
    case 3:
        return std::make_shared<FragileContainer>(number, client, height, length, width, cost, mass, maxPressure);
    case 4:
        return std::make_shared<FragileContainer>(number, client, width, height, length, cost, mass, maxPressure);
    case 5:
        return std::make_shared<FragileContainer>(number, client, height, width, length, cost, mass, maxPressure);
    default:
        return std::make_shared<FragileContainer>(number, client, length, width, height, cost, mass, maxPressure);
    }
}
       
bool FragileContainer::operator==(const FragileContainer& other) const {
    return number == other.number;
}

extern "C" IContainer* createFragileContainer(std::string id, std::string cl_nt, int l, int w, int h, double newcost, double mass, double maxP, double maxT) {
    return new FragileContainer(id, cl_nt, l, w, h, newcost, mass, maxP);
}

void FragileContainer::setId(const std::string& newId)  { number = newId; }

void FragileContainer::setClient(const std::string& newClient) { client = newClient; }

void FragileContainer::setDimensions(int len, int w, int h) { length = len; width = w; height = h; }

void FragileContainer::setCost(double newCost) { cost = newCost; }

void FragileContainer::setMass(double newMass) { mass = newMass; }

void FragileContainer::setMaxPressure(double Pressure) { maxPressure = Pressure; }