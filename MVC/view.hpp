#ifndef STORAGEVIEW_HPP
#define STORAGEVIEW_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../Storage/Storage.hpp"
#include "../Container/AnimalContainer.hpp"
#include "../Container/ExplosiveContainer.hpp"



class StorageView {
public:
    StorageView(const std::string& libDirectory) : libraryManager(libDirectory) {}
    ~StorageView() {}

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
        std::string id, client;
        std::cout << "Enter container ID: ";
        std::cin >> id;
        std::cout << "Enter owner name: ";
        std::cin >> client;

        std::cout << "Choose container type:\n";
        std::cout << "1. Regular container\n";
        std::cout << "2. Fragile container\n";
        std::cout << "3. Refrigerated container\n";
        std::cout << "4. Fragile refrigerated container\n";
        std::cout << "5. Explosive container\n";
        std::cout << "6. Explosive container\n";
        int type;
        std::cin >> type;

        using CreateContainerFunc = IContainer* (*)(std::string, std::string, int, int, int, double, double, double, double);
        CreateContainerFunc createFunc = nullptr;

        switch (type) {
            case 1:
                createFunc = libraryManager.getCreateFunction<CreateContainerFunc>("createRegularContainer");
                break;
            case 2:
                createFunc = libraryManager.getCreateFunction<CreateContainerFunc>("createFragileContainer");
                break;
            case 3:
                createFunc = libraryManager.getCreateFunction<CreateContainerFunc>("createRefrigeratedContainer");
                break;
            case 4:
                createFunc = libraryManager.getCreateFunction<CreateContainerFunc>("createFragileRefrigeratedContainer");
                break;
            case 5:
                createFunc = libraryManager.getCreateFunction<CreateContainerFunc>("createExplosiveContainer");
                break;
            case 6:
                createFunc = libraryManager.getCreateFunction<CreateContainerFunc>("createAnimalContainer");
                break;
            default:
                std::cout << "Invalid container type. Container not added.\n";
                return nullptr;
        }

        if (!createFunc) {
            std::cout << "Error: unable to get create function for the selected container type.\n";
            return nullptr;
        }

        
        int length, width, height;
        double cost, mass, maxPressure = 0.0, maxTemperature = 0.0;

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

        if (type == 2 || type == 4) { 
            std::cout << "Enter maximum pressure: ";
            std::cin >> maxPressure;
        }

        if (type == 3 || type == 4 || type == 6) { 
            std::cout << "Enter maximum temperature: ";
            std::cin >> maxTemperature;
        }
        
        std::shared_ptr<IContainer> container(
            createFunc(id, client, length, width, height, cost, mass, maxPressure, maxTemperature)
        );
        return container;
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

    void promptStorage(int& id, int& length, int& width, int& height, double& temperature){
        std::cout << "Enter Storage ID: ";
        std::cin >> id;
        std::cout << "Enter Storage Length: ";
        std::cin >> length;
        std::cout << "Enter Storage Width: ";
        std::cin >> width;
        std::cout << "Enter Storage Height: ";
        std::cin >> height;
        std::cout << "Enter Storage Temperature: ";
        std::cin >> temperature;
    }


    void displayMessage(const std::string &message) {
        std::cout << message;
    }
    
    LibraryManager libraryManager;

    int selectOperation() {
        int selectedIndex = 0;
        const std::vector<std::string> operations = {
            "Add container",
            "Add container with XYZ coordinates",
            "Remove container",
            "Move container",
            "Rotate container",
            "Show all containers",
            "Show storage information",
            "Exit"
        };
        int totalOperations = operations.size();

        while (true) {

            // std::cout << "\033[2J\033[1;1H";
            // std::cout << "--- Storage Management Menu ---\n";
            
            for (int i = 0; i < operations.size(); ++i) {
                if (i == selectedIndex) {
                    std::cout << "> ";
                } else {
                    std::cout << "  ";
                }
                std::cout << operations[i] << "\n";
            }
            
            char input;
            std::cout << "Use arrow keys to navigate (up: 'w', down: 's', select: 'e', cancel: 'q'): ";
            std::cin >> input;
            
            if (input == 'w') {
                if(selectedIndex > 0){
                    selectedIndex--;
                }else{
                    selectedIndex = totalOperations - 1;
                }
            } else if (input == 's') {
                if (selectedIndex < totalOperations - 1) {
                    selectedIndex++;
                } else {
                    selectedIndex = 0;
                }
            } else if (input == 'e') {
                return selectedIndex;
            } else if (input == 'q') {
                std::cout << "Exiting.\n";
                return -1;
            } else {
                std::cout << "Invalid input. Please use 'w', 's', 'e' or 'q'.\n";
            }
        }
    }
};

#endif