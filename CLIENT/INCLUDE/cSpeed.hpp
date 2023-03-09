/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** cSpeed
*/

#include "iComponent.hpp"
#include "SFML/System/Vector2.hpp"

#pragma once

class cSpeed  final: public iComponent
{
public:
    /**
    * Initialisation of private variables
    */
    cSpeed();
    /**
    * Initialisation with assignement of new values for private variables x and y
    */
    cSpeed(float x, float y);
    /**
    * Initialisation with assignement of new values for private variables x, y and deceleration_rate
    */
    cSpeed(float x, float y, int deceRate);
    cSpeed(cSpeed* cpy);
    /**
    * Add new value to x and y
    */
    void setSpeed(float x, float y);
    void setDeceleration(int newDeceRate);
    void accelerate(float x, float y);
    /**
    * Remove speed by decresing value x and y according to deceleration_rate
    */
    void deccelerate();
    /**
    * Set new x
    */
    void setX(float x);
    /**
    * Set new y
    */
    void setY(float y);
    /**
    * Return a vector of x and y
    */
    sf::Vector2f getSpeed();
    /**
    * Create new componenet speed selon le type renseigné
    */
    eComponentList getComponentType() override;
    /**
    * Get the type of component speed
    */
    iComponent *clone() override;
    void Destroy() { delete this; }
    ~cSpeed();
private:
    /**
    * Private value used for speed component
    */
    float _x;
    float _y;
    int _deceleration_rate;
};
