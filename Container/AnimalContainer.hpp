#ifndef ANIMALCONTAINER_HPP
#define ANIMALCONTAINER_HPP

#include "./I/IContainer.hpp"

/**
 * @struct Animal
 * @brief Structure representing an animal.
 *
 * Contains information about the animal, including its name, age, and weight.
 */
struct Animal {
    std::string name; ///< Name of the animal.
    int age;         ///< Age of the animal.
    double weight;   ///< Weight of the animal.
};

/**
 * @class AnimalContainer
 * @brief Container for storing information about animals.
 *
 * Inherits from the IContainer class and includes additional parameters
 * related to storing animals, such as the container's dimensions and maximum temperature.
 */
class AnimalContainer : public IContainer {
protected:
    std::string number;         ///< Container number.
    std::string client;         ///< Client information.
    int length;                 ///< Container length.
    int width;                  ///< Container width.
    int height;                 ///< Container height.
    double cost;                ///< Container cost.
    double mass;                ///< Container mass.
    double maxTemperature;      ///< Maximum temperature in the container.
    Animal animal;              ///< Animal stored in the container.

public:
    /**
     * @brief Default constructor.
     */
    AnimalContainer(){};

    /**
     * @brief Parameterized constructor.
     * @param number Container number.
     * @param client Client information.
     * @param length Container length.
     * @param width Container width.
     * @param height Container height.
     * @param cost Container cost.
     * @param mass Container mass.
     * @param maxTemperature Maximum temperature in the container.
     * @param animal Animal stored in the container.
     */
    AnimalContainer(std::string number, std::string client, int length, int width, int height, double cost, double mass, double maxTemperature, Animal animal);

    /**
     * @brief Sets the animal in the container.
     * @param animal Animal to be set.
     */
    void setAnimal(const Animal& animal);

    /**
     * @brief Gets the animal from the container.
     * @return The stored animal.
     */
    Animal getAnimal() const;

    /**
     * @brief Creates a new instance of the container as a copy of the current one.
     * @param i Index for copying.
     * @param method Copying method.
     * @return Pointer to the new container instance.
     */
    std::shared_ptr<IContainer> Clone(size_t i = 0, size_t method = 0) override;

    /**
     * @brief Determines the type of the container.
     * @return A string describing the type of container.
     */
    std::string isType() const override;

    /**
     * @brief Gets information about the container.
     * @param output Output stream for displaying information.
     */
    void getInfo(std::ostream& output) const override;

    
    void setId(int X, int Y, int Z) override;
    std::string getId() const override;
    int getLength() const override;
    int getWidth() const override;
    int getHeight() const override;
    std::string getClient() const override;
    double getMass() const override;
    void setId(const std::string& newId) override;
    void setClient(const std::string& newClient) override;
    void setDimensions(int len, int w, int h) override;
    void setCost(double newCost) override;
    void setMass(double newMass) override;

    /**
     * @brief Destructor.
     */
    ~AnimalContainer() override {};
};

#endif