#ifndef LIBRARYMANAGER_HPP
#define LIBRARYMANAGER_HPP

#include <iostream>
#include <vector>
#include <dlfcn.h>
#include <string>
#include <memory>
#include <dirent.h>
#include "../I/IContainer.hpp"


class LibraryManager {
public:
    LibraryManager(const std::string& dir) {
        loadLibraries(dir);
    }

    ~LibraryManager() {
        unloadLibraries();
    }

    std::vector<void(*)(Storage&, std::shared_ptr<IContainer>, ContainerPosition<Point<int>>)> getCheckFunctions() {
        std::vector<void(*)(Storage&, std::shared_ptr<IContainer>, ContainerPosition<Point<int>>)> checkFunctions;
        for (auto library : libraryVector) {
            void* func = dlsym(library, "check");
            if (func != nullptr) {
                checkFunctions.push_back((void(*)(Storage&, std::shared_ptr<IContainer>, ContainerPosition<Point<int>>))func);
            }
        }
        return checkFunctions;
    }

    void loadLibraries(const std::string& dir) {
        DIR* openDir = opendir(dir.c_str());
        if (!openDir) {
            throw std::invalid_argument("Directory not found:" + dir);
        }

        struct dirent* entry;
        while ((entry = readdir(openDir)) != NULL) {
            std::string file(entry->d_name);
            if (file.find(".so") != std::string::npos) {
                std::string path = dir + "/" + file;
                void* library = dlopen(path.c_str(), RTLD_LAZY);
                if (!library) {
                    std::cerr << "Oops, couldn't load the library: " << path << " Error: " << dlerror() << '\n';
                    continue;
                }
                libraryVector.push_back(library);
                
                std::cout << "Successfully uploaded library: " << file << "\n"; 
            }
        }
        closedir(openDir);
    }

    void unloadLibraries() {
        for (void* library : libraryVector) {
            if (dlclose(library) != 0) {
                std::cerr << "Cannot unload library: " << dlerror() << '\n';
            }
        }
        libraryVector.clear();
    }

    template<typename ContainerFunc>
    ContainerFunc getCreateFunction(const std::string& functionName) {
        for (auto library : libraryVector) {
            ContainerFunc func = (ContainerFunc) dlsym(library, functionName.c_str());
            if (func != nullptr) {
                return func;
            }
        }
        std::cerr << "Function " << functionName << " not found in loaded libraries.\n";
        return nullptr;
    }

private:
    std::vector<void*> libraryVector;
};

#endif