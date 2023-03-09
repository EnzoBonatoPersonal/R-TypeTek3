/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

// INCLUDE

#include "Engine.hpp"
#include "../INCLUDE/ClientHandler.hpp"
#include "../../TOOLS/INCLUDE/SafeQueue.hpp"
#include "../../TOOLS/INCLUDE/DataBuffer.hpp"

// DEFINE

/**
* Tag to define state of the game
*/
enum {
    LOBBY = 0,
    PLAYING = 1,
    PAUSE = 2,
};

// CLASS DEFINITION

class Lobby {

    public:

        Lobby() = default;
        Lobby(SafeQueue<RequestInfo> *, SafeQueue<RequestInfo> *);
        ~Lobby();

        // COPPLIEN

        Lobby(const Lobby &other) = default;
        Lobby &operator=(const Lobby &other) = default;

        // FUNCTION

        /**
        * Return _id
        */
        std::string getId();
        /**
        * Change the _status
        */
        void setStatus(int status);
        /**
        * Retutn the number of player in the vector _playerList
        */
        std::size_t getNumberPlayer();
        /**
        * Return true if specified id is a current player
        */
        bool isPlayerHere(std::string id);
        /**
        * Add a player to the vector _playerList
        */
        void addPlayer(ClientHandler player);
        /**
        * Remove a specified player from the vector _playerList
        */
        void removePlayer(ClientHandler player);
        void run();
        void setup(SafeQueue<RequestInfo> *queueToSend, SafeQueue<RequestInfo> * queueReceive);
        int getStatus();
        ClientHandler getPlayerByIndex(std::size_t index);

        // TEMPORARY FUNCTION (DEBUG)

        /**
        * Display in cout the list of the players
        */
        void displayListPlayer();

    protected:
    private:
        /**
        * Variables used for the management of the lobby
        */
        int _status;

        std::string _id;
        std::vector<ClientHandler> _playerList;

        SafeQueue<RequestInfo> *_queueToSend;
        SafeQueue<RequestInfo> *_queueReceive;

        Engine _engine;
};

#endif /* !LOBBY_HPP_ */
