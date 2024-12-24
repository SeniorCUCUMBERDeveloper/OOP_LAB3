#include "ExplosiveContainer.hpp"
#include "ExplosiveContainerCheck.hpp"


std::string ExplosiveContainer::isType() const{
    return "Explosive Container";
}

ExplosiveContainer::ExplosiveContainer(){
    number = "0";
    client = "No";
    length = 0;
    width = 0;
    height = 0;
    cost = 0;
    mass = 0;
}

ExplosiveContainer::ExplosiveContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass){
    this->number = number;
    this->client = client;
    this->length = length;
    this->width = width;
    this->height = height;
    this->cost = cost;
    this->mass = mass;
}


extern "C" IContainer* createExplosiveContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass, double maxP, double maxT) {
    return new ExplosiveContainer(number, client, length, width, height, cost, mass);
}


bool CollisionExplasive(const ContainerPosition<Point<int>> firstPosition, const ContainerPosition<Point<int>> secondPosition) {
    int firstMinX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinX(firstPosition);
    int firstMaxX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxX(firstPosition);
    int firstMinY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinY(firstPosition);
    int firstMaxY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxY(firstPosition);
    int firstMinZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinZ(firstPosition);
    int firstMaxZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxZ(firstPosition);
    
    int secondMinX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinX(secondPosition);
    int secondMaxX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxX(secondPosition);
    int secondMinY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinY(secondPosition);
    int secondMaxY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxY(secondPosition);
    int secondMinZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinZ(secondPosition);
    int secondMaxZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxZ(secondPosition);
    
    return (firstMinX <= secondMaxX && firstMaxX >= secondMinX) &&
           (firstMinY <= secondMaxY && firstMaxY >= secondMinY) &&
           (firstMinZ <= secondMaxZ && firstMaxZ >= secondMinZ);
}

void searchExplasive(Storage& storage, ContainerPosition<Point<int>>& position){
    std::shared_mutex localMutex;
    int minX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinX(position);
    int maxX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxX(position);
    int minY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinY(position);
    int maxY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxY(position);
    int minZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinZ(position);
    std::vector<std::pair<ContainerPosition<Point<int>>, std::shared_ptr<IContainer>>> vector;
    {
    std::shared_lock<std::shared_mutex> lock(localMutex);
    vector = storage.getALLcontainers();
    }
    for (const auto& container : vector) {
        if (container.second->isType() == "Explosive Container" && CollisionExplasive(position, container.first)) {
            throw std::invalid_argument("Explosive Containers cannot stand together");
        }
    }
}


extern "C" void check(Storage& storage, std::shared_ptr<IContainer> container, ContainerPosition<Point<int>> pos){
    if(container == nullptr){
        throw std::invalid_argument("Container is not fragile");
    }
    if(container->isType() == "Explosive Container"){
        ContainerPosition copy = pos;
        copy.LLDown.x--; copy.LLDown.y--; copy.LLDown.z--;
        copy.LLUp.x--; copy.LLUp.y--; copy.LLUp.z++;
        copy.LRUp.x++; copy.LRUp.y--; copy.LRUp.z++;
        copy.LRDown.x++; copy.LRDown.y--; copy.LRDown.z--;
        copy.RRUp.x++; copy.RRUp.y++; copy.RRUp.z++;
        copy.RRDown.x++; copy.RRDown.y++; copy.RRDown.z--;
        copy.RLDown.x--; copy.RLDown.y++; copy.RLDown.z--;
        copy.RLUp.x--; copy.RLUp.y++; copy.RLUp.z++;
        searchExplasive(storage, copy);
    }
}