/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud
** File description:
** Server
*/

#include "../INCLUDE/Server.hpp"

Server::Server(boost::asio::io_service& io_service): _socket(io_service, udp::endpoint(udp::v4(), 8080))
{
    //CommunicationTools com(_endpoint, io_service);
    start_receive();
}

Server::~Server()
{
}

// VECTOR FUNCTION

template<typename T>
bool Server::isIdTaken(std::vector<T> myVector, std::string id)
{
    for (std::size_t cnt = 0; cnt < myVector.size(); cnt++) {
        if (myVector.at(cnt).getId() == id)
            return (true);
    }
    return (false);
}

template<typename T>
std::size_t Server::findIndexById(std::vector<T> myVector, std::string id)
{
    for (std::size_t cnt = 0; cnt < myVector.size(); cnt++) {
        if (myVector.at(cnt).getId() == id)
            return (cnt);
    }
    return (0);
}

// FUNCTON

void Server::start_send(boost::asio::ip::udp::endpoint endpoint, std::string request, std::string msg, std::string id)
{
    std::ostringstream archive_stream;
    boost::archive::binary_oarchive archive(archive_stream);
    _sendBuffer._request = _prot.sendProtocol(request, id, msg);
    archive << _sendBuffer;
    boost::shared_ptr<std::string> message(new std::string(archive_stream.str()));

    _socket.async_send_to(boost::asio::buffer(*message), endpoint,
            boost::bind(&Server::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Server::start_receive()
{
    _socket.async_receive_from(boost::asio::buffer(_buffer, MAX_LENGHT), _endpoint, boost::bind(&Server::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

}

DataBuffer Server::recupMessage(char *buffer, std::size_t bytes_received)
{
    DataBuffer data;
    std::string buf(buffer, bytes_received);
    std::istringstream archive_stream(buf);
    boost::archive::binary_iarchive archive(archive_stream);
    archive >> data;
    _receiveBuffer._request = _prot.receiveProtocol(data._request);
    _requestInfo._request = _prot.getStrFromProtocol(_receiveBuffer._request, "REQUEST");
    _requestInfo._id = _prot.getStrFromProtocol(_receiveBuffer._request, "ID");
    _requestInfo._firstValue = _prot.getStrFromProtocol(_receiveBuffer._request, "VALUE_1");
    _requestInfo._secondValue = _prot.getStrFromProtocol(_receiveBuffer._request, "VALUE_2");
    if (_requestInfo._request != "RUN") {
        std::cout << "REQUEST = " << _requestInfo._request;
        std::cout << "ID = " << _requestInfo._id;
        std::cout << " VALUE_1 = " << _requestInfo._firstValue;
        std::cout << " VALUE_2 = " << _requestInfo._secondValue << std::endl;
    }
    return (data);
}

void Server::handle_receive(const boost::system::error_code& error, std::size_t bytes_received)
{
    if (!error || error == boost::asio::error::message_size)
    {
        _receiveBuffer = recupMessage(_buffer, bytes_received);

        if (_requestInfo._request == "CONNECT")
            connect(_requestInfo._firstValue);
        else if (_requestInfo._request == "CREATE")
            createLobby(_requestInfo._secondValue);
        else if (_requestInfo._request == "JOIN")
            joinLobby(_requestInfo._secondValue, _requestInfo._firstValue);
        else if (_requestInfo._request == "START")
            startGame(_requestInfo._firstValue, _requestInfo._secondValue);
        else if (_requestInfo._request == "RUN")
            start_send(_endpoint, "OK", "RUN", "Server");
        else {
            std::cout << "REQUETE = " << _requestInfo._request << std::endl;
            start_send(_endpoint, "OK", _requestInfo._request, "Server");
        }
        start_receive();
    }
}

void Server::handle_send(boost::shared_ptr<std::string> /*message*/,const boost::system::error_code& /*error*/,std::size_t /*bytes_transferred*/)
{
}

// COMMANDE FUNCTION

void Server::connect(std::string id)
{
    if (isIdTaken(_clientList, id) == false) {
        _clientList.push_back(ClientHandler(id, _endpoint));
        start_send(_endpoint, "OK", "", "Server");
        std::cout << id << " viens de se connecter" << std::endl;
    }
    else {
        start_send(_endpoint, "KO", "FAILED", "Server");
        std::cout << "FAILED" << std::endl;
    }
}

void Server::createLobby(std::string id)
{
    if (isIdTaken(_lobbyList, id) == false) {
        _lobbyList.push_back(Lobby(id));
        start_send(_endpoint, "OK", "", "Server");
        std::cout << id << "Lobby crée" << std::endl;
    }
    else {
        start_send(_endpoint, "KO", "FAILED", "Server");
        std::cout << "FAILED" << std::endl;
    }
}

void Server::joinLobby(std::string idLobby, std::string idClient)
{
    std::size_t cnt = 0;
    std::string _name = "test";

    idLobby = "test";
    if (_lobbyList.size() == 0)
        createLobby("test");
    for (;cnt < _lobbyList.size(); cnt++) {
        if (_lobbyList.at(cnt).getNumberPlayer() == 4)
            createLobby(_name.append(std::to_string(cnt)));
    }
    idLobby = _name;
    if (isIdTaken(_lobbyList, idLobby) == true) {
        std::size_t index = findIndexById(_lobbyList, idLobby);
        if (_lobbyList.at(index).isPlayerHere(idClient) == false) {
            _lobbyList.at(index).addPlayer(ClientHandler(idClient, _endpoint));
            start_send(_endpoint, "OK", "", "Server");
            std::cout << idClient << " a rejoint le lobby" << std::endl;
        }
        else {
            start_send(_endpoint, "KO", "FAILED", "Server");
            std::cout << "FAILED" << std::endl;
        }
    }
    else {
        start_send(_endpoint, "KO", "FAILED", "Server");
        std::cout << "FAILED" << std::endl;
    }
}

void Server::startGame(std::string idClient, std::string idLobby)
{
    idLobby = idLobby;
    for (std::size_t cnt = 0; cnt < _lobbyList.size(); cnt++) {
        if (_lobbyList.at(cnt).isPlayerHere(idClient) == true) {
            for (std::size_t count = 0; count < _lobbyList.at(count).getNumberPlayer(); count++) {
                _lobbyList.at(cnt).setStatus(PLAYING);
                start_send(_endpoint, "OK", "GAME", "Server");
            }
        }
    }
    // if (isIdTaken(_lobbyList, idLobby) == true) {
    //     std::size_t index = findIndexById(_lobbyList, idLobby);
    //     _lobbyList.at(index).setStatus(PLAYING);
    //     start_send(_endpoint, "OK", "GAME", "Server");
    //     std::cout << idLobby << "Partie Lancé" << std::endl;
    // }
    // else {
    //     start_send(_endpoint, "KO", "FAILED", "Server");
    //     std::cout << "FAILED" << std::endl;
    // }
}