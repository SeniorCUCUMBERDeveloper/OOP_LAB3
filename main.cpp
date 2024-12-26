#include <iostream>
#include "./MVC/controller.hpp"
#include "./MVC/view.hpp"
#include "./Storage/Storage.hpp"



int main() {
    std::string libDirectory = "./libs";
    StorageView view(libDirectory);
    int id;
    int length;
    int width;
    int height;
    double temperature;


    view.promptStorage(id, length, width, height, temperature);

    Storage storage(id, length, width, height, temperature);
    StorageController controller(storage, view);
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    int choice;

    do {
        try {
            choice = view.selectOperation();

            switch (choice) {
                case 0:
                    controller.addContainer();
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    break;
                case 1:
                    controller.addContainerXYZ();
                    break;
                case 2:
                    controller.removeContainer();
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    break;
                case 3:
                    controller.moveContainer();
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    break;
                case 4:
                    controller.rotateContainer();
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    break;
                case 5:
                    controller.displayContainers();
                    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
                    break;
                case 6:
                    controller.displayStorageInfo();
                    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
                    break;
                case 7:
                    view.displayMessage("Exiting.\n");
                    return 0;
                case -1:
                    return 0;
                default:
                    throw std::invalid_argument("Invalid choice. Please try again.");
            }
        } catch (const std::exception& e) {
            std::cerr << "An error occurred: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(4000));
            choice = 0;
        }
    } while (choice != 8);
}