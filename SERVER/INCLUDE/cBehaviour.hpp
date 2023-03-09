/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** cBehaviour
*/

#include "iComponent.hpp"

#pragma once

enum eBehaviour {
    NEAR_PLAYER,
    SPIDER,
    CHARGER,
    EXFLY,
    BPOO,
    SPOO,
};

class cBehaviour final: public iComponent
{
public:
    cBehaviour(eBehaviour);
    std::string getNextMove();
    eComponentList getComponentType() override;
    eBehaviour getBehaviourType();
    iComponent *clone() override;
    void Destroy() { delete this; }
    ~cBehaviour();
private:
    eBehaviour _ia;
};