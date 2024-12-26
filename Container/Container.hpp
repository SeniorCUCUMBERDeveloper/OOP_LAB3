#ifndef CONTAINER_HPP
#define CONTAINER_HPP


#include <iostream>
#include <string>
#include <memory>
#include "./I/IContainer.hpp"

/**
 * @class Container
 * @brief A class representing a container with various attributes.
 *
 * The class implements the IContainer interface and holds information about the container,
 * including its dimensions, mass, cost, and client.
 */

class Container: public IContainer{
    protected:
        std::string number;                      
        std::string client;              
        int length, width, height;       
        double cost;                     
        double mass;
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes the container with empty values and zeros.
         */
        Container() 
        : number(0), client(""), length(0), width(0), height(0), cost(0), mass(0) {}

        /**
         * @brief Parameterized constructor.
         * @param number Container ID.
         * @param client Client that owns the container.
         * @param length Length of the container.
         * @param width Width of the container.
         * @param height Height of the container.
         * @param cost Cost of the container.
         * @param mass Mass of the container.
         */
        Container(std::string number, std::string client, int length, int width, int height, double cost, double mass){
            this->number = number;
            this->client = client;
            this->length = length;
            this->width = width;
            this->height = height;
            this->cost = cost;
            this->mass = mass;
        }
        /**
         * @brief Get the length of the container.
         * @return Length of the container.
         */
        int getLength() const override{
            return length;
        }
        /**
         * @brief Get the width of the container.
         * @return Width of the container.
         */
        int getWidth() const override{
            return width;
        }
        /**
         * @brief Get the height of the container.
         * @return Height of the container.
         */
        int getHeight() const override{
            return height;
        }
        /**
         * @brief Get the ID of the container.
         * @return ID of the container.
         */
        std::string getId() const override{
            return number;
        }
        /**
         * @brief Get the mass of the container.
         * @return Mass of the container.
         */
        double getMass() const override{
            return mass;
        }
        /**
         * @brief Get the client of the container.
         * @return Client of the container.
         */
        std::string getClient() const override{
            return client;
        }
        /**
         * @brief Set the ID of the container.
         * @param X First part of the ID.
         * @param Y Second part of the ID.
         * @param Z Third part of the ID.
         */
        void setId(int X, int Y, int Z) override{
            number = std::to_string(X) + "_" + std::to_string(Y) + "_" + std::to_string(Z);
        }
        /**
         * @brief Output information about the container.
         * @param output Output stream.
         */

        void getInfo(std::ostream& output) const override{
            output << "Container ID: " << number << std::endl;
            output << "Client: " << client << std::endl;
            output << "Dimensions: " << length << "x" << width << "x" << height << std::endl;
            output << "Cost: $" << cost << std::endl;
            output << "Mass: " << mass << " kg" << std::endl;
        };
        /**
         * @brief Create a clone of the container with the ability to change dimensions.
         * @param i Unused parameter.
         * @param method Method of changing dimensions.
         * @return A smart pointer to the new container.
         */
        std::shared_ptr<IContainer> Clone(size_t i = 0, size_t method = 0) override{
            switch (method)
            {
            case 0:
                return std::make_shared<Container>(number, client, length, width, height, cost, mass);
            case 1:
                return std::make_shared<Container>(number, client, width, length, height, cost, mass);
            case 2:
                return std::make_shared<Container>(number, client, length, height, width, cost, mass);
            case 3:
                return std::make_shared<Container>(number, client, height, length, width, cost, mass);
            case 4:
                return std::make_shared<Container>(number, client, width, height, length, cost, mass);
            case 5:
                return std::make_shared<Container>(number, client, height, width, length, cost, mass);
            default:
                return std::make_shared<Container>(number, client, length, width, height, cost, mass);
            }
        }
        /**
         * @brief Equality operator overload.
         * @param other Another container to compare.
         * @return true if the containers are equal, otherwise false.
         */
        bool operator==(const Container& other) const {
            return number == other.number;
        }
        /**
         * @brief Get the type of the container.
         * @return Type of the container.
         */
        std::string isType() const override{
            return "Default Container";
        }
        /**
         * @brief Destructor.
         */
        ~Container() override {}

};


#endif