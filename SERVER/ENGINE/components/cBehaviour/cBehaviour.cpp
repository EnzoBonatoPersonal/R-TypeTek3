#include "../../../INCLUDE/cBehaviour.hpp"

cBehaviour::cBehaviour(eBehaviour b)
{
    _ia = b;
}

cBehaviour::~cBehaviour()
{
}

eComponentList cBehaviour::getComponentType()
{
    return behaviour;
}

iComponent* cBehaviour::clone()
{
    return new cBehaviour(_ia);
}

eBehaviour cBehaviour::getBehaviourType()
{
    return _ia;    
}
