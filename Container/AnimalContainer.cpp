#include "AnimalContainer.hpp"
#include "../Storage/Storage.hpp"


AnimalContainer::AnimalContainer(std::string number, std::string client, int lenght, int width, int height, double cost, double mass, double maxTemperature, Animal animal) : number(number), client(client),
length(lenght), width(width), height(height), cost(cost), maxTemperature(maxTemperature), animal(animal){
    this->mass = animal.weight + mass;
};


void AnimalContainer::setAnimal(const Animal& animal){
    this->animal = animal;
}


Animal AnimalContainer::getAnimal() const{
    return animal;
}


std::shared_ptr<IContainer> AnimalContainer::Clone(size_t i, size_t method){
    switch (method)
    {
    case 0:
        return std::make_shared<AnimalContainer>(number, client, length, width, height, cost, mass, maxTemperature, animal);
    case 1:
        return std::make_shared<AnimalContainer>(number, client, width, length, height, cost, mass, maxTemperature, animal);
    case 2:
        return std::make_shared<AnimalContainer>(number, client, length, height, width, cost, mass, maxTemperature, animal);
    case 3:
        return std::make_shared<AnimalContainer>(number, client, height, length, width, cost, mass, maxTemperature, animal);
    case 4:
        return std::make_shared<AnimalContainer>(number, client, width, height, length, cost, mass, maxTemperature, animal);
    case 5:
        return std::make_shared<AnimalContainer>(number, client, height, width, length, cost, mass, maxTemperature, animal);
    default:
        return std::make_shared<AnimalContainer>(number, client, length, width, height, cost, mass, maxTemperature, animal);
    }
}


std::string AnimalContainer::isType() const{ return "Animal Container";}


void AnimalContainer::getInfo(std::ostream& output) const {
    output << "Container ID: " << number << std::endl;
    output << "Client: " << client << std::endl;
    output << "Dimensions: " << length << "x" << width << "x" << height << std::endl;
    output << "Cost: $" << cost << std::endl;
    output << "Mass: " << mass << " kg" << std::endl;
    output << "Max Temperature: " << maxTemperature << std::endl;
    output << "Animal type: " << animal.name << std::endl;
    output << "Animal age: " << animal.age << std::endl;
    output << "Animal weight: " << animal.weight << std::endl;
}


extern "C" IContainer* createAnimalContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass, double maxPressure, double maxTemperature) {
    Animal animal({"None", 0, 0.0});
    return new AnimalContainer(number, client, length, width, height, cost, mass, maxTemperature, animal);
}

void under_Animal(Storage& storage, ContainerPosition<Point<int>>& positionOne){
    std::shared_mutex mtx;
    std::vector<std::pair<ContainerPosition<Point<int>>, std::shared_ptr<IContainer>>> allContainer;
    {
        std::shared_lock<std::shared_mutex> lock(mtx);
        allContainer = storage.getALLcontainers();
    }
    for (const auto& container : allContainer) {
        const ContainerPosition<Point<int>>& positionTwo = container.first;
        if(container.second->isType() == "Explosive Container"){
            throw std::invalid_argument("Animal container should not be stored in a storage with explosive containers");
        }
        if (container.second->isType() == "Animal Container" && 
        positionOne.LLDown.x <= positionTwo.LRDown.x && positionOne.LRDown.x >= positionTwo.LLDown.x &&
        positionOne.LLDown.y <= positionTwo.RLDown.y && positionOne.RLDown.y >= positionTwo.LLDown.y && 
        positionOne.LLDown.z <= positionTwo.LLUp.z && positionOne.LLUp.z >= positionTwo.LLDown.z) 
        {
            throw std::invalid_argument("Cannot put on a container with pets");
        }
    }
}

extern "C" void checkAnimal(Storage& storage, std::shared_ptr<IContainer> container, ContainerPosition<Point<int>> pos){
    if(container == nullptr){
        throw std::invalid_argument("Error object not founded");
    }
    ContainerPosition position_for_check = pos;
    position_for_check.LLDown.z -= 1;
    position_for_check.LRDown.z -= 1;
    position_for_check.RLDown.z -= 1;
    position_for_check.RRDown.z -= 1;
    under_Animal(storage, position_for_check);
}


void AnimalContainer::setId(int X, int Y, int Z) {
    number = std::to_string(X) + "_" + std::to_string(Y) + "_" + std::to_string(Z);
}

std::string AnimalContainer::getId() const {
    return number;
}

int AnimalContainer::getLength() const {
    return length;
}

int AnimalContainer::getWidth() const {
    return width;
}

int AnimalContainer::getHeight() const {
    return height;
}

std::string AnimalContainer::getClient() const {
    return client;
}

double AnimalContainer::getMass() const {
    return mass;
}

void AnimalContainer::setId(const std::string& newId) {
    number = newId;
}

void AnimalContainer::setClient(const std::string& newClient) {
    client = newClient;
}

void AnimalContainer::setDimensions(int len, int w, int h) {
    length = len;
    width = w;
    height = h;
}

void AnimalContainer::setCost(double newCost) {
    cost = newCost;
}

void AnimalContainer::setMass(double newMass) {
    mass = newMass;
}
