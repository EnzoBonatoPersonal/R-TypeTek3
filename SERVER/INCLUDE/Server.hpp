/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

// INCLUDE

#include <string>
#include <thread>
#include <iterator>
#include <iostream>
#include "Lobby.hpp"
#include "../../TOOLS/INCLUDE/Protocol.hpp"
#include <boost/asio.hpp>
#include "../../TOOLS/INCLUDE/DataBuffer.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "ClientHandler.hpp"
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

// CLASS DEFINITION

class Server {

    public:

        Server(boost::asio::io_service& io_service);
        ~Server();

        // COPPLIEN

        Server(const Server &other) = default;
        Server &operator=(const Server &other) = default;

        // VECTOR FUNCTION

        template<typename T>
        bool isIdTaken(std::vector<T> myVector, std::string id);

        template<typename T>
        std::size_t findIndexById(std::vector<T>, std::string id);

        // FUNCTION

        void start_send(boost::asio::ip::udp::endpoint endpoint, std::string _request, std::string _msg, std::string id);
        void start_receive();
        DataBuffer recupMessage(char *buffer, std::size_t bytes_received);
        void handle_receive(const boost::system::error_code& error, std::size_t);
        void handle_send(boost::shared_ptr<std::string> , const boost::system::error_code& , std::size_t );

        // COMMANDE FUNCTION

        void connect(std::string id);
        void createLobby(std::string id);
        void joinLobby(std::string idLobby, std::string idClient);
        void startGame(std::string idClient, std::string idLobby);

    protected:
    private:

        // DATA MESSAGE

        char _buffer[MAX_LENGHT] = "";

        Protocol _prot;
        DataBuffer _sendBuffer;
        DataBuffer _receiveBuffer;

        RequestInfo _requestInfo;

        // COMMUNICATION

        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint _endpoint;

        // CLIENT MANAGEMENT

        std::vector<ClientHandler> _clientList;
        std::vector<Lobby> _lobbyList;
};

#endif /* !SERVER_HPP_ */
