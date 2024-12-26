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


extern "C" IContainer* createExplosiveContainer(std::string id, std::string cl_nt, int l, int w, int h, double cost, double mass, double maxP, double maxT) {
    return new ExplosiveContainer(id, cl_nt, l, w, h, cost, mass);
}


bool ContainEntity(const ContainerPosition<Point<int>> pos1, const ContainerPosition<Point<int>> pos2){
    int pos1MinX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinX(pos1);
    int pos1MaxX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxX(pos1);
    int pos1MinY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinY(pos1);
    int pos1MaxY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxY(pos1);
    int pos1MinZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinZ(pos1);
    int pos1MaxZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxZ(pos1);
    

    int pos2MinX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinX(pos2);
    int pos2MaxX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxX(pos2);
    int pos2MinY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinY(pos2);
    int pos2MaxY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxY(pos2);
    int pos2MinZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinZ(pos2);
    int pos2MaxZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxZ(pos2);


    return (pos1MinX <= pos2MaxX && pos1MaxX >= pos2MinX) &&
        (pos1MinY <= pos2MaxY && pos1MaxY >= pos2MinY) &&
        (pos1MinZ <= pos2MaxZ && pos1MaxZ >= pos2MinZ);
}

void searchExplasiveCollision(Storage& storage, ContainerPosition<Point<int>>& position){
    std::vector<std::pair<ContainerPosition<Point<int>>,std::shared_ptr<IContainer>>> result;
    std::shared_mutex localMutex;
    int minX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinX(position);
    int maxX = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxX(position);
    int minY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinY(position);
    int maxY = Octree<Point<int>, std::shared_ptr<IContainer>>::getMaxY(position);
    int minZ = Octree<Point<int>, std::shared_ptr<IContainer>>::getMinZ(position);
    std::vector<std::pair<ContainerPosition<Point<int>>, std::shared_ptr<IContainer>>> current;
    {
    std::shared_lock<std::shared_mutex> lock(localMutex);
    current = storage.getALLcontainers();
    }
    for (const auto& container : current) {
        const ContainerPosition<Point<int>>& containerPos = container.first;
        if(container.second->isType() == "Animal Container"){
            throw std::invalid_argument("Explosive container should not be stored in a storage with animal containers");
        }
        if (container.second->isType() == "Explosive Container" && ContainEntity(position, containerPos)) {
            throw std::invalid_argument("Explosive Containers cannot stand together");
        }
    }
}


extern "C" void checkExplosive(Storage& storage, std::shared_ptr<IContainer> container, ContainerPosition<Point<int>> pos){
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
        searchExplasiveCollision(storage, copy);
    }
}