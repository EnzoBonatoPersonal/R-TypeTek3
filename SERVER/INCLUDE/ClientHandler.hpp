/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** ClientHandler
*/

#ifndef CLIENTHANDLER_HPP_
#define CLIENTHANDLER_HPP_

// INCLUDE

#include <iostream>
#include <boost/asio.hpp>

// DEFINE

/**
* Tag used for the management of the client
*/
enum {
    MENU = 0,
    LOBBY_WAIT = 1,
    MENU_READY = 2,
    IN_GAME = 3,
};

// CLASS DEFINITION

class ClientHandler {

    public:

        ClientHandler() = default;
        ClientHandler(std::string id, boost::asio::ip::udp::endpoint endpoint);
        ~ClientHandler();

        // COPPLIEN

        ClientHandler(const ClientHandler &other) = default;
        ClientHandler &operator=(const ClientHandler &other) = default;

        // FUNCTION

        /**
        * Return the status of the client (enum)
        */
        int getStatus();
        /**
        * Return the client _id
        */
        std::string getId();
        /**
        * Set the client _status
        */
        void setStatus(int status);
        /**
        * Return the cleint _endpoint
        */
        boost::asio::ip::udp::endpoint getEndpoint();

    protected:
    private:

        int _status;
        std::string _id;
        std::string _lobby;
        boost::asio::ip::udp::endpoint _endpoint;

};

#endif /* !CLIENTHANDLER_HPP_ */
