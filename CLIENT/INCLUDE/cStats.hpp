/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** cBehaviour
*/

#include "iComponent.hpp"
#include <vector>

#pragma once

struct tearToShot {
    float angle;
    int offset;
};


class cStats final: public iComponent
{
public:
    cStats();
    iComponent *clone() override;
    eComponentList getComponentType() override;
    int getTearRange();
    int getTearDamage();
    int getBulletNumber();
    float getTearSpeed();
    float getSize();
    float getFirerate();
    int getDeceRate();
    float getPlayerSpeed();
    std::vector<struct tearToShot> getTearToShot();
    void addTearToShot(float angle, int offset);
    void setTearRange(int r);
    void setTearDamage(int d);
    void setBulletNumber(int b);
    void setTearSpeed(float s);
    void setSize(float s);
    void setFirerate(float s);
    void setDeceRate(int d);
    void setPlayerSpeed(float s);

    void increaseTearRange();
    void increaseTearDamage();
    void increaseBulletNumber();
    void increaseTearSpeed();
    void increaseSize();
    void increaseFirerate();
    void increaseDeceRate();
    void increasePlayerSpeed();

    void Destroy() { delete this; }
    ~cStats();
private:
    
    int _tearRange;
    int _tearDamage;
    int _bulletNumber;
    float _tearSpeed;
    float _size;
    float _firerate;
    int _deceRate;
    float _playerSpeed;
    std::vector<tearToShot> _tearToShot;
};