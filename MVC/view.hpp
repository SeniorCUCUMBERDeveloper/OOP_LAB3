#ifndef STORAGEVIEW_HPP
#define STORAGEVIEW_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../Storage/Storage.hpp"
#include "../Container/RefragedContainer.hpp"
#include "../Container/Container.hpp"
#include "../Container/FragileContainer.hpp"
#include "../Container/Frag_and_Ref.hpp"


class StorageView {
public:
    void displayStorageInfo(const Storage& storage) {
        std::cout << "Storage Information:\n";
        std::cout << "Dimensions: " << std::to_string(storage.getLength()) << " x " 
                  << storage.getWidth() << " x " << storage.getHeight() << "\n";
        std::cout << "Temperature: " << storage.getTemperature() << std::endl;
        std::cout << storage.getInfo() << std::endl;
    }


    void displayContainers(const std::vector<std::pair<ContainerPosition<Point<int>>, std::shared_ptr<IContainer>>> &containers) {
        if (containers.empty()) {
            std::cout << "No containers in storage.\n";
            return;
        }
        
        std::cout << "List of containers:\n";
        size_t i = 1;
        for (const auto& containerPair : containers) {
            auto container = containerPair.second;
            std::cout << "Container No. " << std::to_string(i) << std::endl;
            std::cout << "ID: " << container->getId() << " " << container->isType() << std::endl;
            std::cout << "Client: " << container->getClient() << std::endl;
            std::cout << "Length: " << container->getLength() << ", " 
                      << "Width: " << container->getWidth() << ", " 
                      << "Height: " << container->getHeight() << std::endl;
            std::cout << "Mass: " << container->getMass() << std::endl;
            i++;
        }
    }


    std::shared_ptr<IContainer> promptAddContainer() {
        std::string id, name;
        std::cout << "Enter container ID: ";
        std::cin >> id;
        std::cout << "Enter owner name: ";
        std::cin >> name;

        std::cout << "Choose container type:\n";
        std::cout << "1. Regular container\n";
        std::cout << "2. Fragile container\n";
        std::cout << "3. Refrigerated container\n";
        std::cout << "4. Fragile refrigerated container\n";
        int type;
        std::cin >> type;

        int length, width, height;
        double cost, mass;

        std::cout << "Enter length: ";
        std::cin >> length;
        std::cout << "Enter width: ";
        std::cin >> width;
        std::cout << "Enter height: ";
        std::cin >> height;
        std::cout << "Enter cost: ";
        std::cin >> cost;
        std::cout << "Enter mass: ";
        std::cin >> mass;

        switch (type) {
            case 1:
                return std::make_shared<Container>(id, name, length, width, height, cost, mass);
            case 2: {
                double maxPressure;
                std::cout << "Enter maximum pressure: ";
                std::cin >> maxPressure;
                return std::make_shared<FragileContainer>(id, name, length, width, height, cost, mass, maxPressure);
            }
            case 3: {
                double maxTemperature;
                std::cout << "Enter maximum temperature: ";
                std::cin >> maxTemperature;
                return std::make_shared<RefragedContainer>(id, name, length, width, height, cost, mass, maxTemperature);
            }
            case 4: {
                double maxPressure, maxTemperature;
                std::cout << "Enter maximum pressure: ";
                std::cin >> maxPressure;
                std::cout << "Enter maximum temperature: ";
                std::cin >> maxTemperature;
                return std::make_shared<FragileRefragedContainer>(id, name, length, width, height, cost, mass, maxPressure, maxTemperature);
            }
            default:
                std::cout << "Invalid container type. Container not added.\n";
                return nullptr;
        }
    }

    
    void promptMoveContainer(int &x, int &y, int &z) {
        std::cout << "Enter new coordinates (X Y Z): ";
        std::cin >> x >> y >> z;
    }


    void promptAddCoordinates(int &x, int &y, int &z) {
        std::cout << "Enter new coordinates (X Y Z): ";
        std::cin >> x >> y >> z;
    }


    void promptRotateContainer(int &method) {
        std::cout << "Enter rotation method: ";
        std::cin >> method;
    }


    void displayMessage(const std::string &message) {
        std::cout << message;
    }
};

#endif