/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** Client
*/

#include "../INCLUDE/Client.hpp"

Client::Client(boost::asio::io_service& io_service, std::string idPlayer) : _socket(io_service, udp::endpoint(udp::v4(), 0))
{
    boost::asio::ip::udp::resolver resolver(io_service);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "127.0.0.1", "8080");
    boost::asio::ip::udp::resolver::iterator itr = resolver.resolve(query);
    _endpoint = *itr;

    //CommunicationTools com(_endpoint, io_service, "127.0.0.1", "8080");

    _status = CLI_NONE;
    _idPlayer = idPlayer;
    _thread = new boost::thread(&Client::receiveInstruction, this);
    _thread->join();
}

Client::~Client()
{
}

// VECTOR FUNCTION

template<typename T>
bool Client::isIdTaken(std::vector<T> myVector, std::string id)
{
    for (std::size_t cnt = 0; cnt < myVector.size(); cnt++) {
        if (myVector.at(cnt).getId() == id)
            return (true);
    }
    return (false);
}

template<typename T>
std::size_t Client::findIndexById(std::vector<T> myVector, std::string id)
{
    for (std::size_t cnt = 0; cnt < myVector.size(); cnt++) {
        if (myVector.at(cnt).getId() == id)
            return (cnt);
    }
    return (0);
}

// FUNCTION

void Client::start_receive()
{
    _socket.async_receive_from(boost::asio::buffer(_buffer, MAX_LENGHT), _endpoint, boost::bind(&Client::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void thread()
{
  for (int i = 0; i < 5; ++i)
  {
    std::cout << i << '\n';
  }
}

void Client::loop()
{
    //boost::thread myThread{thread};
    //myThread.join();
    start_send("CONNECT", ".", _idPlayer);
    _thread->join();
    start_send("CONNECT", ".", _idPlayer);
    start_send("JOIN", "", _idPlayer);
    start_send("START", "", _idPlayer);
    start_send("RUN", "", _idPlayer);
    //handleRequest();
}

void Client::gameLoop()
{
    start_receive();
}

void Client::start_send(std::string request, std::string msg, std::string id)
{
    _sendBuffer._request = _prot.sendProtocol(request, id, msg);
    std::ostringstream archive_stream;
    boost::archive::binary_oarchive archive(archive_stream);

    archive << _sendBuffer;
    boost::shared_ptr<std::string> message(new std::string(archive_stream.str()));

    _socket.async_send_to(boost::asio::buffer(*message), _endpoint,
            boost::bind(&Client::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Client::handleRequest(void)
{
    std::string value = ".";

    if (_status == CLI_NONE)
        start_send("CONNECT", ".", _idPlayer);
    if (_status == CLI_CONNECT)
        start_send("JOIN", "", _idPlayer);
    if (_status == CLI_JOIN)
        start_send("START", "", _idPlayer);
    if (_status == CLI_START)
        start_send("RUN", "", _idPlayer);
    if (_status == CLI_GAME)
        start_send("RUN", "", _idPlayer);
    start_receive();
}

void Client::recupMessage(char *buffer, std::size_t bytes_received)
{
    std::string buf(buffer, bytes_received);
    std::istringstream archive_stream(buf);
    boost::archive::binary_iarchive archive(archive_stream);
    archive >> _receiveBuffer;
    _receiveBuffer._request = _prot.receiveProtocol(_receiveBuffer._request);
    _requestInfo._request = _prot.getStrFromProtocol(_receiveBuffer._request, "REQUEST");
    _requestInfo._id = _prot.getStrFromProtocol(_receiveBuffer._request, "ID");
    _requestInfo._firstValue = _prot.getStrFromProtocol(_receiveBuffer._request, "VALUE_1");
    _requestInfo._secondValue = _prot.getStrFromProtocol(_receiveBuffer._request, "VALUE_2");
    if (_requestInfo._secondValue != "RUN") {
        std::cout << "REQUEST = " << _requestInfo._request;
        std::cout << "ID = " << _requestInfo._id;
        std::cout << " VALUE_1 = " << _requestInfo._firstValue;
        std::cout << " VALUE_2 = " << _requestInfo._secondValue << std::endl;
    }

}

void Client::handle_receive(const boost::system::error_code& error, std::size_t bytes_received)
{
    std::string _key;

    if (!error || error == boost::asio::error::message_size)
    {
        recupMessage(_buffer, bytes_received);
        if (_status == CLI_NONE && _requestInfo._request == "OK")
            _status = CLI_CONNECT;
        else if (_status == CLI_CONNECT && _requestInfo._request == "OK")
            _status = CLI_JOIN;
        else if (_status == CLI_JOIN && _requestInfo._request == "OK")
            _status = CLI_START;
        else if (_status == CLI_START && _requestInfo._request == "OK") {
            _e.addEntityToGame(1);
            _status = CLI_GAME;
        }
        if (_status == CLI_GAME) {
            _e.mainLoop();
        }
        //loop();
    }
}

void Client::handle_send(boost::shared_ptr<std::string> /*message*/,const boost::system::error_code& /*error*/,std::size_t /*bytes_transferred*/)
{
    //start_receive();
}

void Client::getInstruction()
{
    return (_safeRequest.pop());
}

void Client::receiveInstruction()
{
    _socket.async_receive_from(boost::asio::buffer(_buffer, MAX_LENGHT), _endpoint, boost::bind(&Client::handleInstruction, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Client::sendInstruction(std::string request, std::string msg, std::string id)
{
    _sendBuffer._request = _prot.sendProtocol(request, id, msg);
    std::ostringstream archive_stream;
    boost::archive::binary_oarchive archive(archive_stream);

    archive << _sendBuffer;
    boost::shared_ptr<std::string> message(new std::string(archive_stream.str()));

    _socket.async_send_to(boost::asio::buffer(*message), _endpoint,
            boost::bind(&Client::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Client::handleInstruction(const boost::system::error_code& error, std::size_t bytes_received)
{
    std::string _key;

    if (!error || error == boost::asio::error::message_size)
    {
        recupMessage(_buffer, bytes_received);
        _safeRequest.push(_requestInfo);
    }
    receiveInstruction();
}