/*
** EPITECH PROJECT, 2022
** source
** File description:
** Entity
*/

#include <vector>
#include "iComponent.hpp"
#pragma once

class Entity {
    public:
        /**
        * Initialise an entity with an id and a type
        */
        Entity(size_t id, size_t type);
        void freeMe();
        bool free();
        ~Entity();
    private:
        /**
        * Private variables used to assign entity
        */
        size_t _id;
        size_t _entityType;
        bool _isFree;
};



