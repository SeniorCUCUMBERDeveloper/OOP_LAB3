#include <iostream>
#include "./MVC/controller.hpp"
#include "./MVC/view.hpp"
#include "./Storage/Storage.hpp"

int main() {
    int id;
    int length;
    int width;
    int height;
    double temperature;

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

    Storage storage(id, length, width, height, temperature);
    StorageView view;
    StorageController controller(storage, view);

    int choice;

    do {
        try {
            std::cout << "\n--- Storage Management Menu ---\n"
                      << "1. Add container\n"
                      << "2. Add container with XYZ coordinates\n"
                      << "3. Remove container\n"
                      << "4. Move container\n"
                      << "5. Rotate container\n"
                      << "6. Show all containers\n"
                      << "7. Show storage information\n"
                      << "8. Exit\n"
                      << "Choose an action: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    controller.addContainer();
                    break;
                case 2:
                    controller.addContainerXYZ();
                    break;
                case 3:
                    controller.removeContainer();
                    break;
                case 4:
                    controller.moveContainer();
                    break;
                case 5:
                    controller.rotateContainer();
                    break;
                case 6:
                    controller.displayContainers();
                    break;
                case 7:
                    controller.displayStorageInfo();
                    break;
                case 8:
                    std::cout << "Exiting.\n";
                    break;
                default:
                    throw std::invalid_argument("Invalid choice. Please try again.");
            }
        } catch (const std::exception& e) {
            std::cerr << "An error occurred: " << e.what() << std::endl;
            choice = 0;
        }
    } while (choice != 8);

    return 0;
}