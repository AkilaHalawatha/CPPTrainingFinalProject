#ifndef SOCKET_COMM_H
#define SOCKET_COMM_H

/**
 * @brief  Definition of the SocketComm class
 * @author Akila Halawatha
 */

#include <netinet/in.h>

/**
 * @brief SocketComm class to handle network activities
 */
class SocketComm
{
public:
    /**
     * @brief Establish the server, start listening and connect to client
     *
     * @return Establishing the server is successful
     */
    bool serverListen();

    /**
     * @brief Establish the client and connect to the server
     * @param[in]  ipaddr                 IP address of the server
     *
     * @return Establishing the client is successful
     */
    bool clientConnect(std::string ipaddr);

    /**
     * @brief Write to the socket to send bytes
     * @param[in]  buffer                 Buffer containing the bytes to send
     * @param[in]  len                    Length of the buffer
     *
     * @return Bytes are written successfully
     */
    bool writeToSocket(char* buffer, int len);

    /**
     * @brief Read bytes from the socket
     * @param[out] buffer                 Buffer to fill the read bytes
     * @param[in]  len                    Length of the buffer
     *
     * @return No of bytes read
     */
    int readFromSocket(char* buffer, int len);

    /**
     * @brief Close all network communications
     */
    void closeComm();
private:
    const int m_PORT = 8080;
    int mServerFD = 0;
    int mServerSocket = 0;
    int mClientFD = 0;
    int mClientSocket = 0;
    struct sockaddr_in mAddress;
};

#endif // SOCKET_COMM_H