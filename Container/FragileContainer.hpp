#ifndef FRAGILECONTAINER_HPP
#define FRAGILECONTAINER_HPP

#include "./I/IFragile.hpp"


/**
 * @class FragileContainer
 * @brief A class representing a fragile container.
 *
 * This class implements the IFragileContainer interface and contains
 * attributes related to a fragile container, including its dimensions,
 * cost, mass, and maximum pressure.
 */


class FragileContainer : public IFragileContainer{
    protected:
        std::string number;                      
        std::string client;              
        int length, width, height;       
        double cost;                     
        double mass;
        double maxPressure;
    public:

        /**
         * @brief Parameterized constructor.
         * @param number Container ID.
         * @param client Client that owns the container.
         * @param length Length of the container.
         * @param width Width of the container.
         * @param height Height of the container.
         * @param cost Cost of the container.
         * @param mass Mass of the container.
         * @param maxM Maximum pressure the container can withstand.
         */
        FragileContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass,  double maxM){
            this->number = number;
            this->client = client;
            this->length = length;
            this->width = width;
            this->height = height;
            this->cost = cost;
            this->mass = mass;
            this->maxPressure = maxM;
        }
        /**
         * @brief Get the client of the container.
         * @return Client of the container.
         */

        std::string getClient() const override{
            return client;
        }
        /**
         * @brief Destructor.
         */

        ~FragileContainer() override{}
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
         * @brief Set the ID of the container.
         * @param X First part of the ID.
         * @param Y Second part of the ID.
         * @param Z Third part of the ID.
         */

        void setId(int X, int Y, int Z) override{
            number = std::to_string(X) + "_" + std::to_string(Y) + "_" + std::to_string(Z);
        }
        /**
         * @brief Get the mass of the container.
         * @return Mass of the container.
         */

        double getMass() const override{
            return mass;
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
            output << "MaxPressure: " << maxPressure << std::endl;
        }
    
        std::string isType() const override { return "Fragile"; }
        /**
         * @brief Get the maximum pressure the container can withstand.
         * @return Maximum pressure.
         */

        double getMaxPressure() const override{ return maxPressure; }
        /**
         * @brief Create a clone of the container with the ability to change dimensions.
         * @param i Unused parameter.
         * @param method Method of changing dimensions.
         * @return A smart pointer to the new container.
         */
        std::shared_ptr<IContainer> Clone(size_t i = 0, size_t method = 0) override { 
            switch (method)
            {
            case 0:
                return std::make_shared<FragileContainer>(number, client, length, width, height, cost, mass, maxPressure);
            case 1:
                return std::make_shared<FragileContainer>(number, client, width, length, height, cost, mass, maxPressure);
            case 2:
                return std::make_shared<FragileContainer>(number, client, length, height, width, cost, mass, maxPressure);
            case 3:
                return std::make_shared<FragileContainer>(number, client, height, length, width, cost, mass, maxPressure);
            case 4:
                return std::make_shared<FragileContainer>(number, client, width, height, length, cost, mass, maxPressure);
            case 5:
                return std::make_shared<FragileContainer>(number, client, height, width, length, cost, mass, maxPressure);
            default:
                return std::make_shared<FragileContainer>(number, client, length, width, height, cost, mass, maxPressure);
            }
        }
        /**
         * @brief Equality operator overload.
         * @param other Another container to compare.
         * @return true if the containers are equal, otherwise false.
         */
        bool operator==(const FragileContainer& other) const {
        return number == other.number;
    }
};

#endif