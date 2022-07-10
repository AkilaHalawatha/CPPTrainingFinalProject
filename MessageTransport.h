#ifndef MESSAGE_TRANSPORT_H
#define MESSAGE_TRANSPORT_H

/**
 * @brief  Definition of the MessageTransport class
 * @author Akila Halawatha
 */

#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include "ChatMessage.h"
#include "ChatMessageFactory.h"
#include "SocketComm.h"

/**
 * @brief MessageTransport class to exchange ChatMessages
 */
class MessageTransport
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
    bool clientConnect(std::string ipaddr = "127.0.0.1");

    /**
     * @brief Send ChatMessage to the send queue
     * @param[in]  upChatMsg              Unique pointer of the ChatMessage
     *
     * @return ChatMessage sending is successful
     */
    bool sendMessageToQueue(std::unique_ptr<ChatMessage> upChatMsg);

    /**
     * @brief Read ChatMessage from the receive queue
     *
     * @return Unique pointer of the read ChatMessage
     */
    std::unique_ptr<ChatMessage> getMessageFromQueue();

    /**
     * @brief Run ChatMessage sending and receiving threads
     *
     * @return None
     */
    void runSendRecvTasks();

    /**
     * @brief Close the transport and stop read/write threads
     */
    bool close();
private:
    std::queue<std::unique_ptr<ChatMessage>> mSendQueue;
    std::queue<std::unique_ptr<ChatMessage>> mReceiveQueue;
    SocketComm mSocketComm;
    ChatMessageFactory mChatMessageFactory;
    std::mutex mSendMux;
    std::mutex mReceiveMux;
    bool mRunSendTask = false;
    bool mRunRecvTask = false;
    std::thread mSendThread;
    std::thread mReceiveThread;
};

#endif // MESSAGE_TRANSPORT_H