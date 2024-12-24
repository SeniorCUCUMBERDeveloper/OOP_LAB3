#include "Container.hpp"


Container::Container(std::string number, std::string client, int length, int width, int height, double cost, double mass){
    this->number = number;
    this->client = client;
    this->length = length;
    this->width = width;
    this->height = height;
    this->cost = cost;
    this->mass = mass;
}


int Container::getLength() const {
    return length;
}


int Container::getWidth() const{
    return width;
}
    
int Container::getHeight() const{
    return height;
}
    
std::string Container::getId() const{
    return number;
}

double Container::getMass() const{
    return mass;
}

std::string Container::getClient() const{
    return client;
}

void Container::setId(int X, int Y, int Z){
    number = std::to_string(X) + "_" + std::to_string(Y) + "_" + std::to_string(Z);
}

void Container::getInfo(std::ostream& output) const{
    output << "Container ID: " << number << std::endl;
    output << "Client: " << client << std::endl;
    output << "Dimensions: " << length << "x" << width << "x" << height << std::endl;
    output << "Cost: $" << cost << std::endl;
    output << "Mass: " << mass << " kg" << std::endl;
};

std::shared_ptr<IContainer> Container::Clone(size_t i, size_t method){
    switch (method)
    {
    case 0:
        return std::make_shared<Container>(number, client, length, width, height, cost, mass);
    case 1:
        return std::make_shared<Container>(number, client, width, length, height, cost, mass);
    case 2:
        return std::make_shared<Container>(number, client, length, height, width, cost, mass);
    case 3:
        return std::make_shared<Container>(number, client, height, length, width, cost, mass);
    case 4:
        return std::make_shared<Container>(number, client, width, height, length, cost, mass);
    case 5:
        return std::make_shared<Container>(number, client, height, width, length, cost, mass);
    default:
        return std::make_shared<Container>(number, client, length, width, height, cost, mass);
    }
}

bool Container::operator==(const Container& other) const {
    return number == other.number;
}

std::string Container::isType() const{
    return "Default Container";
}

extern "C" IContainer* createRegularContainer(std::string id, std::string cl_nt, int l, int w, int h, double cost, double mass, double maxP, double maxT) {
    return new Container(id, cl_nt, l, w, h, cost, mass);
}

void Container::setId(const std::string& newId) { number = newId; }

void Container::setClient(const std::string& newClient) { client = newClient; }

void Container::setDimensions(int len, int w, int h) { length = len; width = w; height = h; }

void Container::setCost(double newCost) { cost = newCost; }

void Container::setMass(double newMass) { mass = newMass; }