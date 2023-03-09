/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// INCLUDE

#include <ctime>
#include <string>
#include <thread>
#include <queue>
#include <iterator>
#include <iostream>
#include "Engine.hpp"
#include "../../TOOLS/INCLUDE/Protocol.hpp"
#include <boost/asio.hpp>
#include "../../TOOLS/INCLUDE/DataBuffer.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>

// DEFINE

using boost::asio::ip::udp;

/**
* Tag used to defne the client status
*/
enum {
    CLI_NONE = 0,
    CLI_CONNECT = 1,
    CLI_JOIN = 2,
    CLI_START = 3,
    CLI_GAME = 4,
};

// CLASS DEFINITION

class Client {

    public:

        /**
        * Initialise client ip and port
        */
        Client(boost::asio::io_service& io_service, std::string _idPlayer);
        ~Client();

        // COPPLIEN

        Client(const Client &other) = default;
        Client &operator=(const Client &other) = default;

        // VECTOR FUNCTION

        /**
        * Return true if the client and the id match
        */
        template<typename T>
        bool isIdTaken(std::vector<T> myVector, std::string id);

        /**
        * Retunr index of the vector acording to the id
        */
        template<typename T>
        std::size_t findIndexById(std::vector<T>, std::string id);

        // FUNCTION

        /**
        * Start loop of the client in acording to the status of it
        */
        void loop();
        /**
        * Get in the client loop to be able to receive data
        */
        void gameLoop();
        void start_send(std::string request, std::string msg, std::string id);
        void start_receive();
        /**
        * Send data in acording to the status of the client
        */
        void handleRequest();
        /**
        * Get all values of the protocol using the protocol function
        */
        void recupMessage(char *buffer, std::size_t bytes_received);
        void handle_receive(const boost::system::error_code& error, std::size_t);
        void handle_send(boost::shared_ptr<std::string> , const boost::system::error_code& , std::size_t );

        void getInstruction();
        void receiveInstruction();
        void sendInstruction(std::string request, std::string msg, std::string id);
        void handleInstruction(const boost::system::error_code& error, std::size_t);

    protected:
    private:

        // INFORMATION

        int  _status;
        std::string _idPlayer;

        // DATA MESSAGE

        char _buffer[MAX_LENGHT] = "";

        Protocol _prot;
        DataBuffer _sendBuffer;
        DataBuffer _receiveBuffer;

        RequestInfo _requestInfo;

        // COMMUNICATION

        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint _endpoint;

        std::queue<RequestInfo> _safeRequest;

        // ENGINE

        boost::thread *_thread;
        Engine _e;
};

#endif /* !CLIENT_HPP_ */
