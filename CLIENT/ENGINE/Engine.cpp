/*
** EPITECH PROJECT, 2022
** source
** File description:
** Engine
*/

#include "../INCLUDE/Engine.hpp"

Engine::Engine(SafeQueue<RequestInfo> *queueReceive, SafeQueue<RequestInfo> *queueSend)
{
    _isWindowOnFocus = true;
     _queueSend = queueSend;
     _queueReceive = queueReceive;
    _window = new sf::RenderWindow(sf::VideoMode(1920, 960), "rType");
    _window->setFramerateLimit(60);
    _offset = {0, 0};
    addToIntRegister("MENU", 0);
    addToIntRegister("MENU_BIS", 0);
    addToIntRegister("OFFS_X", 0);
    addToIntRegister("OFFS_Y", 0);
    addToIntRegister("ROUND_NB", 1);
    addToIntRegister("ANIMATION_ROUND", 1);
    addToIntRegister("IS_BOSS", 0);
    addToIntRegister("PLAYER_INDEX", -1);
    addToIntRegister("SKILL_POINTS", 10);
    addToIntRegister("DAMAGE_COST", 1);
    addToIntRegister("BULLET_NB_COST", 5);
    addToIntRegister("FIRERATE_COST", 2);
    addToIntRegister("PLAYER1", -1);
    addToIntRegister("PLAYER2", -1);
    addToIntRegister("PLAYER3", -1);
    addToIntRegister("PLAYER4", -1);
    _menuState = GAME_SCENE;
    font.loadFromFile("assets/font2.ttf");
    t.setFont(font);
    t.setFillColor(sf::Color::Green);
    t.setCharacterSize(21);
}

Engine::~Engine()
{
    
}

size_t Engine::addEntityToGame(size_t entity)
{
    this->_entitiesManager.addEntity(entity);
    size_t s = _entitiesManager.getFreePlace();
    this->_componentsManager.addEntity(entity, s);
    return s;
}

size_t Engine::addEntityToGame(size_t entity, sf::Vector2f pos)
{
    this->_entitiesManager.addEntity(entity);
    size_t s = _entitiesManager.getFreePlace();
    this->_componentsManager.addEntity(entity, s, pos);
    return s;
}


void Engine::check()
{
    _componentsManager.check();
}

void Engine::sControl()
{
    if (_isWindowOnFocus == false)
        return;
    for (size_t i = 0; i != _componentsManager.getControllableComponents().size(); i++) {
        if (_componentsManager.getControllableComponents()[i]) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                RequestInfo temp;
                temp._request = "MOVE";
                temp._id = std::to_string(i);
                temp._firstValue = "DOWN";
                temp._secondValue = "0";
                (*_queueSend).push(temp);
                if (_componentsManager.getSpeedComponents()[i])
                    _componentsManager.getSpeedComponents()[i]->setY(10);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                RequestInfo temp2;
                temp2._request = "MOVE";
                temp2._id = std::to_string(i);
                temp2._firstValue = "UP";
                temp2._secondValue = "0";
                (*_queueSend).push(temp2);
                if (_componentsManager.getSpeedComponents()[i])
                    _componentsManager.getSpeedComponents()[i]->setY(-10);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                RequestInfo temp3;
                temp3._request = "MOVE";
                temp3._id = std::to_string(i);
                temp3._firstValue = "LEFT";
                temp3._secondValue = "0";
                (*_queueSend).push(temp3);
                if (_componentsManager.getSpeedComponents()[i])
                    _componentsManager.getSpeedComponents()[i]->setX(-10);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                RequestInfo temp4;
                temp4._request = "MOVE";
                temp4._id = std::to_string(i);
                temp4._firstValue = "RIGHT";
                temp4._secondValue = "0";
                (*_queueSend).push(temp4);
                if (_componentsManager.getSpeedComponents()[i])
                    _componentsManager.getSpeedComponents()[i]->setX(10);
            }
        }
    }
}

void Engine::sSpeed()
{
    for (size_t i = 0; i != _componentsManager.getSpeedComponents().size(); i++) {
        if (_componentsManager.getSpeedComponents()[i]) {
            _componentsManager.getSpeedComponents()[i]->deccelerate();
        }
    }
}

void Engine::sCollision()
{
    for (size_t i = 0; i != _componentsManager.getCollisionsComponents().size(); i++) {
        if (_componentsManager.getCollisionsComponents()[i]) {
            if (_componentsManager.getCollisionsComponents()[i]->getCollisionType() == eCollisionType::collision1) {
                sf::IntRect r = _componentsManager.getGraphicalComponents()[i]->getHitbox();
                sf::Vector2f s = _componentsManager.getSpeedComponents()[i]->getSpeed();
                if (r.top + s.y <= 0)
                    _componentsManager.getSpeedComponents()[i]->setY(0 - r.top);
                if (r.left + s.x <= 0)
                    _componentsManager.getSpeedComponents()[i]->setX(0 - r.left);
                if (r.top + r.height + s.y >= 960)
                    _componentsManager.getSpeedComponents()[i]->setY(960 - (r.top + r.height));
                if (r.left + r.width + s.x >= 1920)
                    _componentsManager.getSpeedComponents()[i]->setX(1920 - (r.left + r.width));
            }
            if (_componentsManager.getCollisionsComponents()[i]->getCollisionType() == eCollisionType::collision4 && _componentsManager.getSpeedComponents()[i]) {
                sf::IntRect r = _componentsManager.getGraphicalComponents()[i]->getHitbox();
                sf::Vector2f s = _componentsManager.getSpeedComponents()[i]->getSpeed();
                if (r.top + s.y <= 0)
                    _componentsManager.getSpeedComponents()[i]->setY(_componentsManager.getSpeedComponents()[i]->getSpeed().y * -1);
                if (r.left + s.x <= 0)
                    _componentsManager.getSpeedComponents()[i]->setX(_componentsManager.getSpeedComponents()[i]->getSpeed().x * -1);
                if (r.top + s.y + r.height >= 960)
                    _componentsManager.getSpeedComponents()[i]->setY(_componentsManager.getSpeedComponents()[i]->getSpeed().y * -1);
                if (r.left + r.width + s.x >= 1920)
                    _componentsManager.getSpeedComponents()[i]->setX(_componentsManager.getSpeedComponents()[i]->getSpeed().x * -1);
            }
        }
    }
    for (size_t i = 0; i != _componentsManager.getCollisionsComponents().size(); i++) {
        if (_componentsManager.getCollisionsComponents()[i]) {
            for (size_t j = 0; j != _componentsManager.getCollisionsComponents().size(); j++) {
                if (_componentsManager.getCollisionsComponents()[j]) {
                    if ((_componentsManager.getCollisionsComponents()[i]->getCollisionType() == collision2 or _componentsManager.getCollisionsComponents()[i]->getCollisionType() == collision1) && (_componentsManager.getCollisionsComponents()[j]->getCollisionType() == collision3 or _componentsManager.getCollisionsComponents()[j]->getCollisionType() == collision4)) {
                        if (_componentsManager.getGraphicalComponents()[i]->getHitbox().intersects(_componentsManager.getGraphicalComponents()[j]->getHitbox()) or _componentsManager.getGraphicalComponents()[j]->getHitbox().intersects(_componentsManager.getGraphicalComponents()[i]->getHitbox())) {
                            _componentsManager.getCollisionsComponents()[i]->decreaseLife(_componentsManager.getCollisionsComponents()[j]->getBodyDamage());
                            _componentsManager.getCollisionsComponents()[j]->decreaseLife(_componentsManager.getCollisionsComponents()[i]->getBodyDamage());
                        }
                    }
                }
            }
        }
    }
}


void Engine::sUpdateLife()
{
    for (size_t i = 0; i != _componentsManager.getCollisionsComponents().size(); i++) {
        if (_componentsManager.getCollisionsComponents()[i] && _componentsManager.getGraphicalComponents()[i]) {
            if (_componentsManager.getCollisionsComponents()[i]) {
                if (_componentsManager.getGraphicalComponents()[i]->getSprite().getPosition().x < -100 or _componentsManager.getGraphicalComponents()[i]->getSprite().getPosition().x > 2100 or _componentsManager.getCollisionsComponents()[i]->getLife() <= 0) {
                    if (getFromIntRegister("PLAYER_INDEX") == i) {
                        exit(0);
                    }
                    removeEntity(i);
                }
            }
        }
    }
}


void Engine::sPlayerFire()
{
    _componentsManager.getGraphicalComponents()[getFromIntRegister("PLAYER_INDEX")]->setTimingMilliseconds(150 * _componentsManager.getStatsComponents()[getFromIntRegister("PLAYER_INDEX")]->getFirerate());
    for (size_t i = 0; i != _componentsManager.getControllableComponents().size(); i++) {
        if (_componentsManager.getControllableComponents()[i]) {
            if (_componentsManager.getGraphicalComponents()[i]->isActualFrame(1)) {                
                for (int j = 0; j != _componentsManager.getStatsComponents()[i]->getBulletNumber(); j++) {
                    size_t s = addEntityToGame(2, sf::Vector2f(_componentsManager.getGraphicalComponents()[i]->getSprite().getPosition().x + 40, _componentsManager.getGraphicalComponents()[i]->getSprite().getPosition().y + 40 * j));
                    _componentsManager.getSpeedComponents()[s]->accelerate(_componentsManager.getSpeedComponents()[i]->getSpeed().x * _componentsManager.getStatsComponents()[i]->getTearSpeed() , _componentsManager.getSpeedComponents()[i]->getSpeed().y * _componentsManager.getStatsComponents()[i]->getTearSpeed());
                    _componentsManager.getCollisionsComponents()[s]->setBodyDamage(_componentsManager.getStatsComponents()[i]->getTearDamage());
                    _componentsManager.getGraphicalComponents()[s]->getSprite().scale(_componentsManager.getStatsComponents()[i]->getSize(), _componentsManager.getStatsComponents()[i]->getSize());
                }
            }
        }
    }
}

void Engine::sMenuing()
{

    if (getFromIntRegister("MENU") == 1) // Settings
        _offset = {_offset.x + ((-500 - _offset.x) / 15), _offset.y + ((-1000 - _offset.y) / 15)};
    if (getFromIntRegister("MENU") == 0) // Main
        _offset = {_offset.x + ((0 - _offset.x) / 15), _offset.y + ((0 - _offset.y) / 15)};
    if (getFromIntRegister("MENU") == 2) // Rules
        _offset = {_offset.x + ((-1900 - _offset.x) / 15), _offset.y + ((-200 - _offset.y) / 15)};


    for (size_t i = 0; i != _componentsManager.getSceneComponents().size(); i++) {
        if (_componentsManager.getSceneComponents()[i]) {
            if (_componentsManager.getSceneComponents()[i]->getScene() == eGameScene::MENU_SCENE) {
                _componentsManager.getGraphicalComponents()[i]->getSprite().setPosition(0, 0);
                _componentsManager.getGraphicalComponents()[i]->getSprite().move(_offset);
                _window->draw(_componentsManager.getGraphicalComponents()[i]->getSprite());
                if (getFromIntRegister("MENU") == 0) {
                    _componentsManager.getTextComponents()[i]->getText().setString(">");
                    _componentsManager.getTextComponents()[i]->getText().setPosition(650, 350);
                    _componentsManager.getTextComponents()[i]->getText().move(-getFromIntRegister("MENU_BIS") * 10, getFromIntRegister("MENU_BIS") * 125);
                }
                if (getFromIntRegister("MENU") == 1) {
                    if (getFromIntRegister("MENU_BIS") == 0) {
                        _componentsManager.getTextComponents()[i]->getText().setString("<-");
                        _componentsManager.getTextComponents()[i]->getText().setPosition(1240, 1340);
                    }
                    if (getFromIntRegister("MENU_BIS") == 1) {
                        _componentsManager.getTextComponents()[i]->getText().setString(">");
                        _componentsManager.getTextComponents()[i]->getText().setPosition(1160, 1455);
                    }
                    if (getFromIntRegister("MENU_BIS") == 2) {
                        _componentsManager.getTextComponents()[i]->getText().setString(">");
                        _componentsManager.getTextComponents()[i]->getText().setPosition(1170, 1655);
                    }    
                    if (getFromIntRegister("MENU_BIS") == 3) {
                        _componentsManager.getTextComponents()[i]->getText().setString("->");
                        _componentsManager.getTextComponents()[i]->getText().setPosition(1360, 1790);
                    }
                }
                if (getFromIntRegister("MENU") == 2) {
                    _componentsManager.getTextComponents()[i]->getText().setString("<-");
                    _componentsManager.getTextComponents()[i]->getText().setPosition(750, 50);
                }
                _componentsManager.getTextComponents()[i]->getText().move(_offset);
                _window->draw(_componentsManager.getTextComponents()[i]->getText());
            }
        }
    }
}

void Engine::sBehaviour()
{
    for (size_t i = 0; i != _componentsManager.getBehaviourComponents().size(); i++) {
        
        if (_componentsManager.getBehaviourComponents()[i]) {
            
            if (_componentsManager.getBehaviourComponents()[i]->getBehaviourType() == eBehaviour::CHARGER) {
                if (_componentsManager.getGraphicalComponents()[i]->getSprite().getPosition().x < 1500) {
                    _componentsManager.getGraphicalComponents()[i]->changeAnimationLoop("attack");
                    _componentsManager.getSpeedComponents()[i]->setSpeed(-20, 0);
                }
            }
            
            if (_componentsManager.getBehaviourComponents()[i]->getBehaviourType() == eBehaviour::SPIDER) {
                if (_componentsManager.getGraphicalComponents()[i]->isActualFrame(4)) {
                    sf::Vector2f v = _componentsManager.getGraphicalComponents()[getFromIntRegister("PLAYER_INDEX")]->getSprite().getPosition();
                    sf::Vector2f v2 = _componentsManager.getGraphicalComponents()[i]->getSprite().getPosition();
                    sf::Vector2f s = sf::Vector2f((v.x - v2.x) / 25, (v.y - v2.y) / 25);
                    sf::Vector2f ss = s;
                    if (abs(s.x) <= 20) {
                        s.x = 20;
                        if (ss.x < 0)
                            s.x *= -1;
                    }
                    if (abs(s.y) <= 20) {
                        s.y = 20;
                        if (ss.y < 0)
                            s.y *= -1; 
                    }
                    if (abs(s.x) >= 35) {
                        s.x = 35;
                        if (ss.x < 0)
                            s.x *= -1;
                    }
                    if (abs(s.y) >= 35) {
                        s.y = 35;
                        if (ss.y < 0)
                            s.y *= -1; 
                    }
                    _componentsManager.getSpeedComponents()[i]->setSpeed(s.x, s.y);
                }
                if (_componentsManager.getGraphicalComponents()[i]->isActualFrame(11)) {
                    _componentsManager.getSpeedComponents()[i]->setDeceleration(15);
                }
            }
            
            if (_componentsManager.getBehaviourComponents()[i]->getBehaviourType() == EXFLY) {
                sf::Vector2f v = _componentsManager.getGraphicalComponents()[getFromIntRegister("PLAYER_INDEX")]->getSprite().getPosition();
                sf::Vector2f v2 = _componentsManager.getGraphicalComponents()[i]->getSprite().getPosition();
                sf::Vector2f s = sf::Vector2f((v.x - v2.x) / 25, (v.y - v2.y) / 25);
                sf::Vector2f ss = s;
                if (abs(s.x) >= 2) {
                    s.x = 2;
                    if (ss.x < 0)
                        s.x *= -1;
                }
                if (abs(s.y) >= 2) {
                    s.y = 2;
                    if (ss.y < 0)
                        s.y *= -1; 
                }
                if (_componentsManager.getCollisionsComponents()[i]->getLife() == 0) {
                    int x = addEntityToGame(10);
                    _componentsManager.getSpeedComponents()[x]->setSpeed(10, 0);
                    _componentsManager.getGraphicalComponents()[x]->getSprite().setPosition(_componentsManager.getGraphicalComponents()[i]->getSprite().getPosition());
                    x = addEntityToGame(10);
                    _componentsManager.getSpeedComponents()[x]->setSpeed(-10, 0);
                    _componentsManager.getGraphicalComponents()[x]->getSprite().setPosition(_componentsManager.getGraphicalComponents()[i]->getSprite().getPosition());
                    x = addEntityToGame(10);
                    _componentsManager.getSpeedComponents()[x]->setSpeed(0, 10);
                    _componentsManager.getGraphicalComponents()[x]->getSprite().setPosition(_componentsManager.getGraphicalComponents()[i]->getSprite().getPosition());
                    x = addEntityToGame(10);
                    _componentsManager.getSpeedComponents()[x]->setSpeed(0, -10);
                    _componentsManager.getGraphicalComponents()[x]->getSprite().setPosition(_componentsManager.getGraphicalComponents()[i]->getSprite().getPosition());
                }
                _componentsManager.getSpeedComponents()[i]->setSpeed(s.x, s.y);
            }

            if (_componentsManager.getBehaviourComponents()[i]->getBehaviourType() == BPOO) {
                if (_componentsManager.getGraphicalComponents()[i]->getName() == "walk") {
                    if (_componentsManager.getGraphicalComponents()[i]->getSprite().getPosition().x < 1500) {
                        _componentsManager.getCollisionsComponents()[i]->setCollisionType(eCollisionType::collision4);
                        _componentsManager.getSpeedComponents()[i]->setDeceleration(150);
                        _componentsManager.getGraphicalComponents()[i]->changeAnimationLoop("charge");
                    }
                } 
                sf::Vector2f v = _componentsManager.getGraphicalComponents()[getFromIntRegister("PLAYER_INDEX")]->getSprite().getPosition();
                sf::Vector2f v2 = _componentsManager.getGraphicalComponents()[i]->getSprite().getPosition();
                sf::Vector2f s = sf::Vector2f((v.x - v2.x) / 25, (v.y - v2.y) / 25);
                if (_componentsManager.getGraphicalComponents()[i]->getName().find("run") != std::string::npos && abs(_componentsManager.getSpeedComponents()[i]->getSpeed().x + _componentsManager.getSpeedComponents()[i]->getSpeed().y) <= 2) {
                    _componentsManager.getGraphicalComponents()[i]->changeAnimationLoop("charge");
                    _componentsManager.getGraphicalComponents()[i]->update();
                }
                if (_componentsManager.getGraphicalComponents()[i]->isActualFrame(2) && _componentsManager.getGraphicalComponents()[i]->getName().find("charge") != std::string::npos) {
                    if (s.x < 0)
                        _componentsManager.getGraphicalComponents()[i]->changeAnimationLoop("runR");
                    else
                        _componentsManager.getGraphicalComponents()[i]->changeAnimationLoop("runL");
                    _componentsManager.getGraphicalComponents()[i]->update();
                    _componentsManager.getSpeedComponents()[i]->setSpeed(s.x, s.y);
                }
                if (_componentsManager.getCollisionsComponents()[i]->getLife() == 0) {
                    for (int j = 0; j != 3; j++) {
                        sf::Vector2f pos = _componentsManager.getGraphicalComponents()[i]->getSprite().getPosition();                        
                        pos.x += rand() % 4 * 40 + 30;
                        pos.y += rand() % 4 * 40 + 30;
                        addEntityToGame(12, pos);
                    } 
                }
            }

            if (_componentsManager.getBehaviourComponents()[i]->getBehaviourType() == SPOO) {
                if (_componentsManager.getGraphicalComponents()[i]->isActualFrame(3) && std::rand() % 3 == 0) {
                    sf::Vector2f v = _componentsManager.getGraphicalComponents()[getFromIntRegister("PLAYER_INDEX")]->getSprite().getPosition();
                    sf::Vector2f v2 = _componentsManager.getGraphicalComponents()[i]->getSprite().getPosition();
                    sf::Vector2f s = sf::Vector2f((v.x - v2.x) / 55, (v.y - v2.y) / 55);
                    sf::Vector2f ss = s;
                    if (abs(s.x) >= 5) {
                        s.x = 5;
                        if (ss.x < 0)
                            s.x *= -1;
                    }
                    if (abs(s.y) >= 5) {
                        s.y = 5;
                        if (ss.y < 0)
                            s.y *= -1; 
                    }
                    _componentsManager.getSpeedComponents()[i]->setSpeed(s.x, s.y);
                    if (s.x < 0) {
                        _componentsManager.getGraphicalComponents()[i]->changeAnimationLoop("walkR");
                    } else {
                        _componentsManager.getGraphicalComponents()[i]->changeAnimationLoop("walkL");
                    }
                }
            }
        }
    }
}

void Engine::sUpdateMenu(sf::Event t)
{
    if (t.type == sf::Event::TextEntered) {

    }
    if (t.type == sf::Event::KeyReleased) {
        if (t.key.code == sf::Keyboard::Enter) {
            if (getFromIntRegister("MENU") == 0 && getFromIntRegister("MENU_BIS") == 0) {
               _scene = LOBBY_SCENE;
               RequestInfo temp;
               temp._request = "CONNECT";
               temp._firstValue = "";
               temp._secondValue = "";
               (*_queueSend).push(temp);
            }
            if (getFromIntRegister("MENU") == 0 && getFromIntRegister("MENU_BIS") == 1) {
                changeFromIntRegister("MENU", 1);
                changeFromIntRegister("MENU_BIS", 0);
                return;
            }
            if (getFromIntRegister("MENU") == 0 && getFromIntRegister("MENU_BIS") == 2) {
                changeFromIntRegister("MENU", 2);
                changeFromIntRegister("MENU_BIS", 0);
                return;
            }
            if (getFromIntRegister("MENU") == 1 && getFromIntRegister("MENU_BIS") == 0) {
                changeFromIntRegister("MENU", 0);
                changeFromIntRegister("MENU_BIS", 1);
                return;
            }
            if (getFromIntRegister("MENU") == 2 && getFromIntRegister("MENU_BIS") == 0) {
                changeFromIntRegister("MENU", 0);
                changeFromIntRegister("MENU_BIS", 2);
                return;
            }
        }
        if (getFromIntRegister("MENU") == 1) {
            if (t.key.code == sf::Keyboard::Up)
                increaseValueFromIntRegister("MENU_BIS", -1);
            if (t.key.code == sf::Keyboard::Down)
                increaseValueFromIntRegister("MENU_BIS", 1);
            if (getFromIntRegister("MENU_BIS") < 0)
                changeFromIntRegister("MENU_BIS", 3);
            if (getFromIntRegister("MENU_BIS") > 3)
                changeFromIntRegister("MENU_BIS", 0);
        }

        if (getFromIntRegister("MENU") == 0) {
            if (t.key.code == sf::Keyboard::Up)
                increaseValueFromIntRegister("MENU_BIS", -1);
            if (t.key.code == sf::Keyboard::Down)
                increaseValueFromIntRegister("MENU_BIS", 1);
            if (getFromIntRegister("MENU_BIS") < 0)
                changeFromIntRegister("MENU_BIS", 2);
            if (getFromIntRegister("MENU_BIS") > 2)
                changeFromIntRegister("MENU_BIS", 0);
        }
    }
}

void Engine::handleNetworkCommand()
{
}

void Engine::removeEntity(size_t toRemove)
{
    if (_componentsManager.getBehaviourComponents()[toRemove]) {
        delete _componentsManager.getBehaviourComponents()[toRemove];
        _componentsManager.getBehaviourComponents()[toRemove] = nullptr;
    }
    if (_componentsManager.getSpeedComponents()[toRemove]) {
        delete _componentsManager.getSpeedComponents()[toRemove];
        _componentsManager.getSpeedComponents()[toRemove] = nullptr;
    }
    if (_componentsManager.getGraphicalComponents()[toRemove]) {
        delete _componentsManager.getGraphicalComponents()[toRemove];
        _componentsManager.getGraphicalComponents()[toRemove] = nullptr;
    }
    if (_componentsManager.getCollisionsComponents()[toRemove]) {
        delete _componentsManager.getCollisionsComponents()[toRemove];
        _componentsManager.getCollisionsComponents()[toRemove] = nullptr;
    }
    if (_componentsManager.getSceneComponents()[toRemove]) {
        delete _componentsManager.getSceneComponents()[toRemove];
        _componentsManager.getSceneComponents()[toRemove] = nullptr;
    }
    if (_componentsManager.getBehaviourComponents()[toRemove]) {
        delete _componentsManager.getBehaviourComponents()[toRemove];
        _componentsManager.getBehaviourComponents()[toRemove] = nullptr;
    }
    if (_componentsManager.getTextComponents()[toRemove]) {
        delete _componentsManager.getTextComponents()[toRemove];
        _componentsManager.getTextComponents()[toRemove] = nullptr;
    }
    if (_componentsManager.getControllableComponents()[toRemove]) {
        delete _componentsManager.getControllableComponents()[toRemove];
        _componentsManager.getControllableComponents()[toRemove] = nullptr;
    }
    if (_componentsManager.getStatsComponents()[toRemove]) {
        delete _componentsManager.getStatsComponents()[toRemove];
        _componentsManager.getStatsComponents()[toRemove] = nullptr;
    }
    _entitiesManager.removeEntity(toRemove);
}


void Engine::addToStringRegister(std::string key, std::string value)
{
    _strRegister[key] = value;
}

std::string Engine::getFromStringRegister(std::string key)
{
    return _strRegister[key];
}

void Engine::changeFromStringRegister(std::string key, std::string value)
{
    _strRegister[key] = value;
}

void Engine::concatValueToStringRegister(std::string key, std::string value)
{
    _strRegister[key] = _strRegister[key] + value;
}

void Engine::summon_ennemies(int entity, int nb_ennemies)
{
    if (entity == 15 && nb_ennemies == 1) {
        for (int i = 0; i != 3; i++) {
            addEntityToGame(8, sf::Vector2f(2000 + rand() % 100 + 0, rand() % 700 + 200));
            addEntityToGame(11, sf::Vector2f(2000 + rand() % 100 + 0, rand() % 700 + 200));
            addEntityToGame(12, sf::Vector2f(2000 + rand() % 100 + 0, rand() % 700 + 200));
        }
        for (int i = 0; i != 10; i++) {
            addEntityToGame(6, sf::Vector2f(2000 + rand() % 100 + 0, rand() % 700 + 200));
            addEntityToGame(9, sf::Vector2f(2000 + rand() % 100 + 0, rand() % 700 + 200));
        }
    } else {
        if (entity == 8)
            nb_ennemies = 3;
        for (int i = 0; i != nb_ennemies; i++)
            addEntityToGame(entity, sf::Vector2f(2000 + rand() % 100 + 0, rand() % 700 + 200));
    }
}

void Engine::waves()
{
    sf::Time delta_time = sf::seconds(3);
    elapsed_time += clock.restart();
    int nb_ennemies = rand() % 15 + 2;
    std::string buff = "Round ";
    int mon[] = {6, 8, 9, 11, 12};

    while (elapsed_time >= delta_time) {
        if (getFromIntRegister("ANIMATION_ROUND") == 1) {
            if (getFromIntRegister("IS_BOSS") == 1) {
                summon_ennemies(15, 1);
            } else
                summon_ennemies(mon[rand() % 5], nb_ennemies);
            changeFromIntRegister("ANIMATION_ROUND", 0);
        } else {
            increaseValueFromIntRegister("ROUND_NB", 1);
            increaseValueFromIntRegister("SKILL_POINTS", 10);
            if (getFromIntRegister("ROUND_NB") % 5 == 0)
                changeFromIntRegister("IS_BOSS", 1);
            else
                changeFromIntRegister("IS_BOSS", 0);
            changeFromIntRegister("ANIMATION_ROUND", 1);
        }
        elapsed_time -= delta_time;
    }
    for (size_t i = 0; i != _componentsManager.getTextComponents().size(); i++) {
        if (_componentsManager.getTextComponents()[i] && _componentsManager.getSceneComponents()[i]) {
            if (_componentsManager.getSceneComponents()[i]->getScene() == eGameScene::GAME_SCENE) {
                if (getFromIntRegister("IS_BOSS") == 1)
                    buff = "BOSS !!!";
                else
                    buff += std::to_string(getFromIntRegister("ROUND_NB"));
                _componentsManager.getTextComponents()[i]->getText().setString(buff); 
                return;
            }
        }
    }
}

bool Engine::run()
{
    if (!_window->isOpen())
        return false;
    while (_window->pollEvent(_event)) {
        switch (_event.type) {
            case (sf::Event::Closed):
                _window->close();
                break;
            case (sf::Event::TextEntered):
                //if (_scene == MENU_SCENE)
                    //sUpdateMenu(_event);
                break;
            case (sf::Event::KeyReleased):
                if (_scene == MENU_SCENE)
                    sUpdateMenu(_event);
                break;
            case (sf::Event::LostFocus):
                _isWindowOnFocus = false;
                break;
            case (sf::Event::GainedFocus):
                _isWindowOnFocus = true;
                break;
            default:
                break;
        }
    }
    if (_scene == MENU_SCENE) {
        sMenuing();
    } else if (_scene == LOBBY_SCENE) {
        connectToLobby();
    } else {
        if ((*_queueReceive).empty() == false) {
            RequestInfo temp = (*_queueReceive).pop();
            if (temp._request == "POS")
                updatePos(temp);
            if (temp._request == "ADD") {
            }
        }
        waves();
        handleNetworkCommand();
        sSpeed();
        sControl();
        sPlayerFire();
        sCollision();
        sBehaviour();
        sUpgradeMenu();
        sUpdateLife();
        drawGraphical();
        drawUX();
    }
    _window->display();
    _window->clear();
    return true;
}

void Engine::updatePos(RequestInfo temp)
{
    sf::Vector2f pos;
    std::size_t i = std::stoi(temp._id);

    pos.x = std::stoi(temp._firstValue);
    pos.y = std::stoi(temp._secondValue);

    std::cout << "ID = " << i << std::endl;
    if (i != _componentsManager.getGraphicalComponents().size()) {
        if (_componentsManager.getSceneComponents()[i]) {
            if (_componentsManager.getSceneComponents()[i]->getScene() == GAME_SCENE) {
                if (_componentsManager.getSpeedComponents()[i] && _componentsManager.getGraphicalComponents()[i]) {
                    _componentsManager.getGraphicalComponents()[i]->getSprite().move(_componentsManager.getSpeedComponents()[i]->getSpeed());
                }
            }
        }
    }
}

void Engine::addToIntRegister(std::string str, int value)
{
    _intRegister[str] = value;
}

int Engine::getFromIntRegister(std::string str)
{
    return _intRegister.at(str);
}

void Engine::changeFromIntRegister(std::string str, int value)
{
    _intRegister[str] = value;
}

void Engine::increaseValueFromIntRegister(std::string str, int value)
{
    _intRegister[str] += value;
}

void Engine::sUpgradeMenu()
{
    t.setPosition(0, 500);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        if (getFromIntRegister("DAMAGE_COST") <= getFromIntRegister("SKILL_POINTS")) {
            increaseValueFromIntRegister("SKILL_POINTS", -getFromIntRegister("DAMAGE_COST"));
            increaseValueFromIntRegister("DAMAGE_COST", 3);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        if (getFromIntRegister("FIRERATE_COST") <= getFromIntRegister("SKILL_POINTS")) {
            increaseValueFromIntRegister("SKILL_POINTS", -getFromIntRegister("FIRERATE_COST"));
            increaseValueFromIntRegister("FIRERATE_COST", 2);
            _componentsManager.getStatsComponents()[getFromIntRegister("PLAYER_INDEX")]->increaseFirerate();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        if (getFromIntRegister("BULLET_NB_COST") <= getFromIntRegister("SKILL_POINTS")) {
            increaseValueFromIntRegister("SKILL_POINTS", -getFromIntRegister("BULLET_NB_COST"));
            increaseValueFromIntRegister("BULLET_NB_COST", getFromIntRegister("BULLET_NB_COST") * 2);
            _componentsManager.getStatsComponents()[getFromIntRegister("PLAYER_INDEX")]->increaseBulletNumber();
        }
    }
}

void Engine::drawGraphical()
{
    for (size_t i = 0; i != _componentsManager.getGraphicalComponents().size(); i++) {
        if (_componentsManager.getSceneComponents()[i]) {
            if (_componentsManager.getSceneComponents()[i]->getScene() == GAME_SCENE) {
                if (_componentsManager.getSpeedComponents()[i] && _componentsManager.getGraphicalComponents()[i]) {
                    _componentsManager.getGraphicalComponents()[i]->getSprite().move(_componentsManager.getSpeedComponents()[i]->getSpeed());
                }  
                if (_componentsManager.getTextComponents()[i] && getFromIntRegister("ANIMATION_ROUND") == 1) {
                    _window->draw(_componentsManager.getTextComponents()[i]->getText());
                }
                if (_componentsManager.getGraphicalComponents()[i] && _componentsManager.getCollisionsComponents()[i]) {
                    if (_componentsManager.getCollisionsComponents()[i]->isInvulnerable()) {
                        _componentsManager.getGraphicalComponents()[i]->getSprite().setColor(sf::Color(255, 255, 255, 100));
                    } else {
                        _componentsManager.getGraphicalComponents()[i]->getSprite().setColor(sf::Color(255, 255, 255, 255));
                    }
                }
                if (_componentsManager.getGraphicalComponents()[i]) {
                    _componentsManager.getGraphicalComponents()[i]->update();
                    _componentsManager.getGraphicalComponents()[i]->display(*_window);
                }
            }
        }
    }
}

void Engine::drawUX()
{   
    t.setCharacterSize(27);
    t.setPosition(0, 10);
    std::string a = "Skill point availible : " + std::to_string(getFromIntRegister("SKILL_POINTS"));
    t.setFillColor(sf::Color::Yellow);
    t.setString(a);
    _window->draw(t);
    t.move(0, 30);

    if (getFromIntRegister("DAMAGE_COST") <= getFromIntRegister("SKILL_POINTS"))
        t.setFillColor(sf::Color::Green);
    else
        t.setFillColor(sf::Color::Red);
    a = "1. Damage | Cost : " + std::to_string(getFromIntRegister("DAMAGE_COST"));
    t.setString(a);
    _window->draw(t);

    if (getFromIntRegister("FIRERATE_COST") <= getFromIntRegister("SKILL_POINTS"))
        t.setFillColor(sf::Color::Green);
    else
        t.setFillColor(sf::Color::Red);
    t.move(0, 30);
    a = "2. Firerate | Cost : " + std::to_string(getFromIntRegister("FIRERATE_COST"));
    t.setString(a);
    _window->draw(t);

    if (getFromIntRegister("BULLET_NB_COST") <= getFromIntRegister("SKILL_POINTS"))
        t.setFillColor(sf::Color::Green);
    else
        t.setFillColor(sf::Color::Red);
    t.move(0, 30);
    a = "3. Bullets | Cost : " + std::to_string(getFromIntRegister("BULLET_NB_COST"));
    t.setString(a);
    _window->draw(t);
}

int Engine::findPlayer()
{
    for (size_t i = 0; i < _componentsManager.getControllableComponents().size(); i++) {
        if (_componentsManager.getControllableComponents()[i])
            return (i);
    }
    return -1;
}

void Engine::connectToLobby()
{
    RequestInfo temp;

    if ((*_queueReceive).empty() == false) {
        temp = (*_queueReceive).pop();
        if (temp._request == "PLAYABLE")
            _indexPlayer = std::stoi(temp._firstValue) + 1;
        if (temp._request == "ADD") {
            if (temp._id == "1") {
                if (std::stoi(temp._firstValue) == _indexPlayer) {
                    addEntityToGame(1);
                    std::string toRegister = "PLAYER";
                    toRegister.append(temp._firstValue);
                    changeFromIntRegister(toRegister, (_componentsManager.getGraphicalComponents().size() - 1));
                    addToIntRegister("PLAYER_INDEX", findPlayer());
                    std::cout << "PLAYER = " << findPlayer() << std::endl;
                }
                else {
                    addEntityToGame(13);
                    std::string toRegister = "PLAYER";
                    toRegister.append(temp._firstValue);
                    changeFromIntRegister(toRegister, (_componentsManager.getGraphicalComponents().size() - 1));
                    addToIntRegister(toRegister, (_componentsManager.getGraphicalComponents().size() - 1));
                    std::cout << "PLAYER OTHER = " << (_componentsManager.getGraphicalComponents().size() - 1) << std::endl;
                }
                if (temp._secondValue == "LAST")
                    _scene = GAME_SCENE;
            }
        }
    }
}
