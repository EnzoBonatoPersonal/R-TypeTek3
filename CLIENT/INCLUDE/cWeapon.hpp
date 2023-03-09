/*
** EPITECH PROJECT, 2022
** source
** File description:
** Weapon
*/

#include "iComponent.hpp"

#pragma once

class cWeapon  final: public iComponent {
    public:
        cWeapon(int damage, float firerate);
        /**
        * Get the type of component weapon
        */
        eComponentList getComponentType() override;
        /**
        * Create new componenet weapon in according to the giver type
        */
        iComponent *clone() override;
        virtual void Destroy() { delete this; }
        ~cWeapon();
    private:
        /**
        * Private value used for weapon component
        */
        int _damage;
        float _firerate;
};