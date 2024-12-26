#ifndef REF_HPP
#define REF_HPP


#include "./I/IRefragedContainer.hpp"
#include <iostream>
/**
 * @class RefragedContainer
 * @brief A class representing a refrigerated container.
 *
 * This class implements the IRefragedContainer interface and encapsulates
 * the properties of a refrigerated container, including its dimensions,
 * cost, mass, and maximum temperature.
 */
class RefragedContainer : public IRefragedContainer{
    protected:
        std::string number;                      
        std::string client;              
        int length, width, height;       
        double cost;                     
        double mass;
        double maxTemperature;
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
     * @param maxT Maximum temperature the container can withstand.
     */
    RefragedContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass, double maxT){
        this->number = number;
        this->client = client;
        this->length = length;
        this->width = width;
        this->height = height;
        this->cost = cost;
        this->mass = mass;
        this->maxTemperature = maxT;
    }
    /**
     * @brief Destructor.
     */
    ~RefragedContainer() override{}
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
     * @brief Get the client of the container.
     * @return Client of the container.
     */
    std::string getClient() const override{
        return client;
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
        output << "MaxTemperature: " << maxTemperature << std::endl;
    }

    std::string isType() const override { return "Refraged";}
    /**
     * @brief Get the maximum temperature the container can withstand.
     * @return Maximum temperature.
     */
    double getMaxTemperature() const override{
        return maxTemperature;
    }
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
            return std::make_shared<RefragedContainer>(number, client, length, width, height, cost, mass, maxTemperature);
        case 1:
            return std::make_shared<RefragedContainer>(number, client, width, length, height, cost, mass, maxTemperature);
        case 2:
            return std::make_shared<RefragedContainer>(number, client, length, height, width, cost, mass, maxTemperature);
        case 3:
            return std::make_shared<RefragedContainer>(number, client, height, length, width, cost, mass, maxTemperature);
        case 4:
            return std::make_shared<RefragedContainer>(number, client, width, height, length, cost, mass, maxTemperature);
        case 5:
            return std::make_shared<RefragedContainer>(number, client, height, width, length, cost, mass, maxTemperature);
        default:
            return std::make_shared<RefragedContainer>(number, client, length, width, height, cost, mass, maxTemperature);
        }
    }
    /**
     * @brief Equality operator overload.
     * @param other Another container to compare.
     * @return true if the containers are equal, otherwise false.
     */
    bool operator==(const RefragedContainer& other) const {
        return number == other.number;
    }
};

#endif