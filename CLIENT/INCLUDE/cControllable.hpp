/*
** EPITECH PROJECT, 2022
** source
** File description:
** Weapon
*/

#include "iComponent.hpp"

#pragma once

class cControllable final: public iComponent {
    public:
        cControllable();
        /**
        * return true or false if an entity with this component is controlable
        */
        bool isControllable();
        /**
        * Create new componenet controlable selon le type renseigné
        */
        eComponentList getComponentType() override;
        /**
        * Get the type of component controlable
        */
        iComponent *clone() override;
        void Destroy() { delete this; }
        ~cControllable();
    private:
        /**
        * True or false if an entity is controlable
        */
        bool _isControllable;
};