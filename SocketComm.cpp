/**
 * @brief  Implementation of the SocketComm class
 * @author Akila Halawatha
 */

#include "Logger.h"
#include "SocketComm.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

/**
 * @brief Establish the server, start listening and connect to client
 *
 * @return Establishing the server is successful
 */
bool SocketComm::serverListen()
{
    bool ret = false;
	int opt = 1;
	int addrlen = sizeof(mAddress);

    do
    {
		Logger::log(INFO, "Establishing server");

		// Check if the server or client is already running
		if(mServerFD || mServerSocket || mClientSocket)
		{
			Logger::log(ERROR, "Server or client is already initiated");
			ret = false;
            break;
		}

		// Create server socket
        if ((mServerFD = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		{
            Logger::log(ERROR, "Server socket creation failed, Err : " 
				+ to_string(mServerFD));
			ret = false;
            break;
        }

		// Attaching socket to the port
		if (setsockopt(mServerFD, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt)))
		{
			Logger::log(ERROR, "setsockopt failed");
			ret = false;
            break;
		}
		mAddress.sin_family = AF_INET;
		mAddress.sin_addr.s_addr = INADDR_ANY;
		mAddress.sin_port = htons(m_PORT);

		// Binding socket to the port
		if (bind(mServerFD, (struct sockaddr*)&mAddress, sizeof(mAddress)) < 0)
		{
			Logger::log(ERROR, "Server binding to socket failed");
			ret = false;
            break;
		}

		// Listen on the port
		if (listen(mServerFD, 3) < 0)
		{
			Logger::log(ERROR, "Listening on port failed");
			ret = false;
            break;
		}

		// Accept the client connection
		if ((mServerSocket = accept(mServerFD, (struct sockaddr*)&mAddress,
				(socklen_t*)&addrlen)) < 0)
		{
			Logger::log(ERROR, "Client connection accepting failed, Err : " 
					+ to_string(mServerSocket));
			ret = false;
            break;
		}

		Logger::log(INFO, "Successfully established server and connected to the client");
		ret = true;

	} while (false);

    return ret;
}

/**
 * @brief Establish the client and connect to the server
 * @param[in]  ipaddr                 IP address of the server
 *
 * @return Establishing the client is successful
 */
bool SocketComm::clientConnect(string ipaddr){
	bool ret = false;
	int opt = 1;

    do
    {
		Logger::log(INFO, "Establishing client");

		// Check if the server or client is already running
		if(mServerFD || mServerSocket || mClientSocket)
		{
			Logger::log(ERROR, "Server or client is already initiated");
			ret = false;
            break;
		}

		// Create client socket
        if ((mClientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
            Logger::log(ERROR, "Client socket creation failed, Err : " 
					+ to_string(mClientSocket));
			ret = false;
            break;
        }

		// Server address
		mAddress.sin_family = AF_INET;
		mAddress.sin_addr.s_addr = INADDR_ANY;
		mAddress.sin_port = htons(m_PORT);
		if (inet_pton(AF_INET, const_cast<char*>(ipaddr.c_str()),
			&mAddress.sin_addr) <= 0)
		{
			Logger::log(ERROR, "Invalid IP address");
			ret = false;
            break;
		}

		// Connect to the server
		if ((mClientFD = connect(mClientSocket, (struct sockaddr*)&mAddress,
			sizeof(mAddress))) < 0)
		{
			Logger::log(ERROR, "Connect to server failed, Err : " + to_string(mClientFD));
			ret = false;
            break;
		}

		Logger::log(INFO, "Successfully established client and connected to the server");
		ret = true;
	} while (false);

	return ret;
}

/**
 * @brief Write to the socket to send bytes
 * @param[in]  buffer                 Buffer containing the bytes to send
 * @param[in]  len                    Length of the buffer
 *
 * @return Bytes are written successfully
 */
bool SocketComm::writeToSocket(char* buffer, int len)
{
	bool ret = false;
	int noOfSent;

    do
    {
		if(mServerSocket)
		{
			noOfSent = send(mServerSocket, buffer, len, 0);
		}
		else if (mClientSocket)
		{
			noOfSent = send(mClientSocket, buffer, len, 0);
		}
		else
		{
			Logger::log(ERROR, "Connection to socket is not established");
			ret = false;
            break;
		}

		if(noOfSent < len)
		{
			Logger::log(ERROR, "Less no of bytes written to the socket : Available:" 
				+ to_string(len) + ",Sent:" + to_string(noOfSent));
			ret = false;
            break;
		}

		Logger::log(INFO, "Successfully written " + to_string(len) + " bytes to the socket");
		ret = true;
	} while (false);

	return ret;
}

/**
 * @brief Read bytes from the socket
 * @param[out] buffer                 Buffer to fill the read bytes
 * @param[in]  len                    Length of the buffer
 *
 * @return No of bytes read
 */
int SocketComm::readFromSocket(char* buffer, int len)
{
	int ret = 0;
	int noOfSent;

    do
    {
		if(mServerSocket)
		{
			ret = read(mServerSocket, buffer, len);
		}
		else if (mClientSocket)
		{
			ret = read(mClientSocket, buffer, len);
		}
		else
		{
			Logger::log(ERROR, "Connection to socket is not established");
			ret = 0;
            break;
		}

		if(ret < 0)
		{
			Logger::log(ERROR, "Reading failed with error : " + to_string(ret));
            break;
		}

		Logger::log(INFO, "Successfully read " + to_string(len) + " bytes from the socket");
	} while (false);

	return ret;
}

/**
 * @brief Close all network communications
 */
void SocketComm::closeComm()
{
	// Closing the server socket if available
	if(mServerFD)
	{
		close(mServerSocket);
	}

	// Shutdown the server if available
	if(mServerFD)
	{
		shutdown(mServerFD, SHUT_RDWR);
	}

	// Closing the client FD if available
	if(mClientFD)
	{
		close(mClientFD);
	}

	Logger::log(INFO, "Successfully closed SocketComm");
	
	mServerSocket = 0;
	mServerFD = 0;
	mClientSocket = 0;
	mClientSocket = 0;
}
