#ifndef CONTAINERPOSITION_HPP
#define CONTAINERPOSITION_HPP
#include "Point.hpp"
#include <memory>

template <typename T>
struct ContainerPosition{
  T LLDown, LLUp;
  T LRDown, LRUp;
  T RRDown, RRUp;
  T RLDown, RLUp;

  ContainerPosition(){}
  ContainerPosition(T llDown, T llUp, T lrDown, T lrUp, 
                      T rrDown, T rrUp, T rlDown, T rlUp)
        : LLDown(llDown), LLUp(llUp), LRDown(lrDown), LRUp(lrUp),
          RRDown(rrDown), RRUp(rrUp), RLDown(rlDown), RLUp(rlUp) {}
//delete
  bool operator==(const ContainerPosition<T>& other) const {
        return LLDown == other.LLDown && LLUp == other.LLUp &&
               LRDown == other.LRDown && LRUp == other.LRUp &&
               RRDown == other.RRDown && RRUp == other.RRUp &&
               RLDown == other.RLDown && RLUp == other.RLUp;
    }

    bool operator<(const ContainerPosition<T>& other) const {
        return std::tie(LLDown, LLUp, LRDown, LRUp, RRDown, RRUp, RLDown, RLUp) <
               std::tie(other.LLDown, other.LLUp, other.LRDown, other.LRUp, other.RRDown, other.RRUp, other.RLDown, other.RLUp);
    }
};


template<typename T>
class ContainerHandler {
public:
    static auto getLength(T& container) { return container.getLength(); }
    static auto getWidth(T& container) { return container.getWidth(); }
    static auto getHeight(T& container) { return container.getHeight(); }
};


template<typename T>
class ContainerHandler<T*> {
public:
    static auto getLength(T* container) { return container->getLength(); }
    static auto getWidth(T* container) { return container->getWidth(); }
    static auto getHeight(T* container) { return container->getHeight(); }
};


template<typename T>
class ContainerHandler<std::unique_ptr<T>> {
public:
    static auto getLength(const std::unique_ptr<T>& container) { return container->getLength(); }
    static auto getWidth(const std::unique_ptr<T>& container) { return container->getWidth(); }
    static auto getHeight(const std::unique_ptr<T>& container) { return container->getHeight(); }
};


template<typename T>
class ContainerHandler<std::shared_ptr<T>> {
public:
    static auto getLength(const std::shared_ptr<T>& container) { return container->getLength(); }
    static auto getWidth(const std::shared_ptr<T>& container) { return container->getWidth(); }
    static auto getHeight(const std::shared_ptr<T>& container) { return container->getHeight(); }
};

#endif