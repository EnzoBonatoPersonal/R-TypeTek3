#include "../../../INCLUDE/cStats.hpp"

cStats::cStats()
{
    _tearRange = 100;
    _tearSpeed = 1.0;
    _tearDamage = 1;
    _size = 1;
    _bulletNumber = 1;
    _firerate = 1;
    _deceRate = 1;
    _playerSpeed = 1;
}

iComponent* cStats::clone()
{
    return new cStats();
}

eComponentList cStats::getComponentType()
{
    return stats;
}

cStats::~cStats()
{

}

float cStats::getPlayerSpeed()
{
    return _playerSpeed;
}

int cStats::getDeceRate()
{
    return _deceRate;
}

float cStats::getFirerate()
{
    return _firerate;
}

float cStats::getSize()
{
    return _size;
}

float cStats::getTearSpeed()
{
    return _tearSpeed;
}

int cStats::getBulletNumber()
{
    return _bulletNumber;
}

int cStats::getTearDamage()
{
    return _tearDamage;
}

int cStats::getTearRange()
{
    return _tearRange;
}

void cStats::setDeceRate(int d)
{
    _deceRate = d;
}

void cStats::setPlayerSpeed(float s)
{
    _playerSpeed = s;
}

void cStats::setFirerate(float s)
{
    _firerate = s;
}

void cStats::setSize(float s)
{
    _size = s;
}

void cStats::setTearSpeed(float s)
{
    _tearSpeed = s;
}

void cStats::setBulletNumber(int b)
{
    _bulletNumber = b;
}

void cStats::setTearDamage(int d)
{
    _tearDamage = d;
}

void cStats::setTearRange(int r)
{
    _tearRange = r;
}

void cStats::addTearToShot(float angle, int offset)
{
    tearToShot s;
    s.angle = angle;
    s.offset = offset;
    _tearToShot.push_back(s);
}

std::vector<struct tearToShot> cStats::getTearToShot()
{
    return _tearToShot;
}

void cStats::increaseTearRange()
{
    _tearRange += 1;
}

void cStats::increaseTearDamage()
{
    _tearDamage += 1;
}

void cStats::increaseBulletNumber()
{
    _bulletNumber += 1;
}

void cStats::increaseTearSpeed()
{
    _tearSpeed += 1;
}

void cStats::increaseSize()
{
    _size += 1;
}

void cStats::increaseFirerate()
{
    _firerate *= 0.9;
}

void cStats::increaseDeceRate()
{
    _deceRate += 30;
}

void cStats::increasePlayerSpeed()
{
    _playerSpeed *= 1.1;
}
