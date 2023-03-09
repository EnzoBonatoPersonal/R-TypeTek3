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
    cSpeed();
    cSpeed(float x, float y);
    cSpeed(float x, float y, int deceRate);
    cSpeed(cSpeed* cpy);
    void setSpeed(float x, float y);
    void setDeceleration(int newDeceRate);
    void accelerate(float x, float y);
    void deccelerate();
    void setX(float x);
    void setY(float y);
    sf::Vector2f getSpeed();
    eComponentList getComponentType() override;
    iComponent *clone() override;
    void Destroy() { delete this; }
    ~cSpeed();
private:
    float _x;
    float _y;
    int _deceleration_rate;
};
