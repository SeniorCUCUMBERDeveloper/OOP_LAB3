#ifndef STORAGECONTROLLER_HPP
#define STORAGECONTROLLER_HPP

#include "../Storage/Storage.hpp"
#include "view.hpp"

class StorageController {
public:
    StorageController(Storage &storage, StorageView &view) 
        : storage(storage), view(view) {}

    void addContainer() {
        auto container = view.promptAddContainer();
        if (container) {
            std::string str = storage.addContainer(container);
            if(str != "_"){
                view.displayMessage("Container added.\n");
            }
        }
    }

    void addContainerXYZ() {
        auto container = view.promptAddContainer();
        int x, y, z;
        if (container) {
            view.promptAddCoordinates(x, y, z);
            storage.addContainer(container, x, y, z);
            view.displayMessage("Container added.\n");
        }
    }

    void removeContainer() {
        std::shared_ptr<IContainer> container = selectContainer();
        if(!container){
            view.displayMessage("Bad.\n");
            return;
        }
        storage.removeContainer(container->getId());
        view.displayMessage("Container removed.\n");
    }

    void moveContainer() {
        int x, y, z;
        std::shared_ptr<IContainer> container = selectContainer();
        if(!container){
            view.displayMessage("Bad.\n");
            return;
        }
        view.promptMoveContainer(x, y, z);
        storage.moveContainer(container->getId(), x, y, z);
        view.displayMessage("Container moved.\n");
    }

    void rotateContainer() {
        std::shared_ptr<IContainer> container = selectContainer();
        if(!container){
            view.displayMessage("Bad.\n");
            return;
        }
        int method;
        view.promptRotateContainer(method);
        storage.rotateContainer(container->getId(), method);
        view.displayMessage("Container rotated.\n");
    }

    void displayContainers() {
        auto containers = storage.getALLcontainers();
        view.displayContainers(containers);
    }

    void displayStorageInfo() {
        view.displayStorageInfo(storage);
    }

private:
    Storage &storage;
    StorageView &view;


    std::shared_ptr<IContainer> selectContainer() {
        std::vector<std::pair<ContainerPosition<Point<int>>, std::shared_ptr<IContainer>>> containers = storage.getALLcontainers();
        if (containers.empty()) {
            view.displayMessage("No containers available to select.\n");
            return nullptr;
        }

        int selectedIndex = 0;
        int totalContainers = containers.size();

        while (true) {
            view.displayMessage("\033[2J\033[1;1H");
            view.displayMessage("Select a container:\n");
            for (int i = 0; i < totalContainers; ++i) {
                auto container = containers[i].second;
                if (i == selectedIndex) {
                    view.displayMessage("> ");
                } else {
                    view.displayMessage("  ");
                }
                view.displayMessage("Container No. " + std::to_string(i + 1) + ": ID = " + container->getId() + ", Type = " + container->isType() + "\n");
            }
            
            char input;
            view.displayMessage("Use arrow keys to navigate (up: 'w', down: 's', select: 'Enter', cancel: 'q'): ");
            std::cin >> input;

            if (input == 'w') {
                if (selectedIndex > 0) {
                    selectedIndex--;
                } else {
                    selectedIndex = totalContainers - 1;
                }
            } else if (input == 's') {
                if (selectedIndex < totalContainers - 1) {
                    selectedIndex++;
                } else {
                    selectedIndex = 0;
                }
            } else if (input == 'e') {
                return containers[selectedIndex].second; 
            } else if (input == 'q') {
                view.displayMessage("Selection cancelled.\n");
                break;
            } else {
                view.displayMessage("Invalid input. Please use 'w', 's', 'e' or 'q'.\n");
            }
        }

        return nullptr;
    }
};

#endif