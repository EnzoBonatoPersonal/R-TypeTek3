/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

// INCLUDE

#include <ctime>
#include <string>
#include <thread>
#include <queue>
#include <iterator>
#include <iostream>
#include "Engine.hpp"
#include "../../TOOLS/INCLUDE/Protocol.hpp"
#include "../../TOOLS/INCLUDE/SafeQueue.hpp"
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

// CLASS DEFINITION

class UDPClient {

    public:

        UDPClient(boost::asio::io_service& io_service, std::string _idPlayer);
        ~UDPClient();

        // COPPLIEN

        UDPClient(const UDPClient &other) = default;
        UDPClient &operator=(const UDPClient &other) = default;

        // FUNCTION

        void receive();
        void handleReceive(const boost::system::error_code& error, std::size_t);

        void send(std::string request, std::string value1, std::string value2, std::string id);
        void handleSend(boost::shared_ptr<std::string> , const boost::system::error_code& , std::size_t );

        void recupMessage(char *buffer, std::size_t bytes_received);

        void joinThread();
        void connect();
        void game();
        void gameSend();
        
        void getRequest();
        
    protected:
    private:

        // INFORMATION

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

        SafeQueue<RequestInfo> _queue;
        SafeQueue<RequestInfo> _queueToSend;

        std::queue<RequestInfo> _safeRequest;
        
};

#endif /* !UDPCLIENT_HPP_ */
