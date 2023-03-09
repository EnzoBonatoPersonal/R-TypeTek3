    /*
** EPITECH PROJECT, 2022
** source
** File description:
** Engine
*/

#include "ComponentsManager.hpp"
#include "EntityManager.hpp"
#include <string.h>
#include "../../TOOLS/INCLUDE/SafeQueue.hpp"
#include "../../TOOLS/INCLUDE/DataBuffer.hpp"

#pragma once

class Engine {
    public:

        Engine(SafeQueue<RequestInfo> *queueReceive, SafeQueue<RequestInfo> *queueSend);
        ~Engine();
        
        size_t addEntityToGame(size_t entity);
        size_t addEntityToGame(size_t entity, sf::Vector2f pos);
        void check();
        void mainLoop();
        
        void sControl(RequestInfo temp);
        void sSpeed();
        void sCollision();
        void sPlayerFire();
        void sUpdateLife();
        void waves();
        void summon_ennemies(int, int);
        void sMenuing();
        void sUpgradeMenu();
        void sBehaviour();
        void drawGraphical(RequestInfo temp);
        void drawUX();
        void sUpdateMenu(sf::Event t);
        
        void handleNetworkCommand();
        
        void removeEntity(size_t r);

        void addToIntRegister(std::string key, int value);
        int getFromIntRegister(std::string key);
        void changeFromIntRegister(std::string key, int value);
        void increaseValueFromIntRegister(std::string key, int value);

        void addToStringRegister(std::string key, std::string value);
        std::string getFromStringRegister(std::string key);
        void changeFromStringRegister(std::string key, std::string value);
        void concatValueToStringRegister(std::string key, std::string value);
        
        int findPlayer();

        bool run();

    private:
        EntityManager _entitiesManager;
        ComponentsManager _componentsManager;
        sf::RenderWindow *_window;
        eGameScene _scene = MENU_SCENE;
        
        std::map<std::string, int> _intRegister;
        std::map<std::string, std::string> _strRegister;

        sf::Event _event;
        sf::Font font;
        sf::Text t;

        int _menuState = 0;
        sf::Vector2f _offset;

        SafeQueue<RequestInfo> *_queueSend;
        SafeQueue<RequestInfo> *_queueReceive;

        sf::Time elapsed_time;
        sf::Clock clock;
};
