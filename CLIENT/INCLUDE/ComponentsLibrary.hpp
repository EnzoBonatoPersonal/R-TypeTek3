/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** ComponentsLibrary
*/


#pragma once

#include <map>
#include "cWeapon.hpp"
#include "cGraphical.hpp"
#include "cControllable.hpp"
#include "cCollision.hpp"
#include "cSpeed.hpp"
#include "cText.hpp"
#include "cScene.hpp"
#include "cStats.hpp"
#include "cBehaviour.hpp"

class ComponentsLibrary {
public:
    /**
    * Initialise all the components for the player and the "tears" = shots
    */
    ComponentsLibrary();
    ~ComponentsLibrary();
    int entityLoaded();
    /**
    * Return a copied vector of the current component vector
    */
    std::vector<iComponent *> getVectorComponents(size_t entity);
private:
    std::map<size_t, std::vector<iComponent *>> _library;
};