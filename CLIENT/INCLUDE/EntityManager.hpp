#include "Entity.hpp"
#include "ComponentsManager.hpp"

#pragma once

class EntityManager
{
public:
    /**
    * Initialisation of var _lastEntity
    */
    EntityManager();
    ~EntityManager();
    /**
    * Add an entity to the vector _entities and increment _lastEntity
    */
    void addEntity(size_t entityType);
    /**
    * Return the position of the last entity in the vector
    */
    size_t getLastEntity();
    size_t getFirstPlaceAvailible();
    size_t getLastEntityCreated();
    size_t getFreePlace();
    void removeEntity(size_t r);
private:
    /**
    * Variables used to manage all entity
    */
    std::vector<Entity> _entities;
    std::vector<size_t> _freePlaces;
    size_t _nextOne;
    size_t _lastEntity;
    size_t _firstPlaceAvailible;
    size_t _lastEntityCreated;
};

























