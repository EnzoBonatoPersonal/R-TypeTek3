/*
** EPITECH PROJECT, 2022
** B-CPP-500-NAN-5-1-rtype-ismael.brossaud [WSL: Ubuntu]
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

// INCLUDE

#include <string>
#include <bitset>
#include <iostream>
#include <iomanip>

#include <stdio.h>
#include <stdarg.h>
#include <math.h>

// DEFINE

// CLASS

class Protocol {

    public:

        Protocol();
        ~Protocol();

        // COPPLIEN

        Protocol(const Protocol &other) = default;
        Protocol &operator=(const Protocol &other) = default;

        // PROTOCOL FUNCTION

        /**
        * Return hexadecimal string of request with one value
        */
        std::string sendProtocol(std::string request, std::string id, std::string value1);
        /**
        * Return hexadecimal string of request with two values
        */
        std::string sendProtocol(std::string request, std::string id, std::string value1, std::string value2);
        /**
        * Return string of the hashed request
        */
        std::string receiveProtocol(std::string hashedProtocol);
        /**
        * Read the protocol string and return the wanted string with a tag
        */
        std::string getStrFromProtocol(std::string protocol, std::string const tag);

    protected:
    private:

        // VARIABLE
        /**
        * Variable used to track the reading of the protocol string
        */
        size_t _parsing;

        // CONVERTION FUNCTION
        /**
        * Take string and return it in binary
        */
        std::string convertTxtToBin(std::string const str);
        /**
        * Take binary string and return it in hexadecimal
        */
        std::string convertBinToHex(std::string const bin);
        /**
        * Take hexadecimal string and return it in string
        */
        std::string convertHexaToTxt(std::string const hexa);

        // REQUEST FUNCTION
        /**
        * Unhash one string of the request and return it
        */
        std::string unhashPartOfProtocol(std::string hashed);
};

#endif /* !PROTOCOL_HPP_ */