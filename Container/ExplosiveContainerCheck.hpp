#ifndef EXPLOSIVECONTAINERCHECK_HPP
#define EXPLOSIVECONTAINERCHECK_HPP
#include "../Storage/Storage.hpp"

bool ContainEntity(const ContainerPosition<Point<int>> pos1, const ContainerPosition<Point<int>> pos2);
void searchExplasiveCollision(Storage& storage, ContainerPosition<Point<int>>& position);


#endif