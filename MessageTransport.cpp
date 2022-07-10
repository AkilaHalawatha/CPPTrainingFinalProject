/**
 * @brief  Implementation of the MessageTransport class
 * @author Akila Halawatha
 */

#include <chrono>
#include "Logger.h"
#include "MessageTransport.h"

using namespace std;

const int BUFF_SIZE = 1000;

/**
 * @brief Establish the server, start listening and connect to client
 *
 * @return Establishing the server is successful
 */
bool MessageTransport::serverListen()
{
    return mSocketComm.serverListen();
}

/**
 * @brief Establish the client and connect to the server
 * @param[in]  ipaddr                 IP address of the server
 *
 * @return Establishing the client is successful
 */
bool MessageTransport::clientConnect(string ipaddr)
{
    return mSocketComm.clientConnect(ipaddr);
}

/**
 * @brief Send ChatMessage to the send queue
 * @param[in]  upChatMsg              Unique pointer of the ChatMessage
 *
 * @return ChatMessage sending is successful
 */
bool MessageTransport::sendMessageToQueue(unique_ptr<ChatMessage> upChatMsg)
{
    lock_guard<mutex> lock(mSendMux);

    if (upChatMsg != nullptr) 
    {
        mSendQueue.push(move(upChatMsg));
    }

    return true;

}

/**
 * @brief Read ChatMessage from the receive queue
 *
 * @return Unique pointer of the read ChatMessage
 */
unique_ptr<ChatMessage> MessageTransport::getMessageFromQueue()
{
    unique_ptr<ChatMessage> ret;
    lock_guard<mutex> lock(mReceiveMux);

    if (mReceiveQueue.empty()) 
    {
        ret = nullptr;
    }
    else
    {
        ret = move(mReceiveQueue.front());
        mReceiveQueue.pop();
    }

    return ret;
}

/**
 * @brief Run ChatMessage sending and receiving threads
 *
 * @return None
 */
void MessageTransport::runSendRecvTasks()
{
    mRunSendTask = true;
    mRunRecvTask = true;

    auto sendMsgTask = [&]() {
        Logger::log(INFO, "sendMsgTask started");

        while(mRunSendTask)
        {
            this_thread::sleep_for(chrono::milliseconds(200));

            unique_ptr<ChatMessage> upChatMsg;

            {
                lock_guard<mutex> lock(mSendMux);
                if (!mSendQueue.empty())
                {
                    upChatMsg = move(mSendQueue.front());
                    mSendQueue.pop();
                }
                else
                {
                    continue;
                }
            }

            unique_ptr<char[]> msgBytes = upChatMsg->encodeMessage();
            int msgLn = ChatMessage::getDataLen(msgBytes) + ChatMessage::MSG_HEADER_LEN;
            mSocketComm.writeToSocket(msgBytes.get(), msgLn);
        }

        Logger::log(INFO, "sendMsgTask end");
    };

    auto readMsgTask = [&]() {
        Logger::log(INFO, "readMsgTask started");

        // TODO : Complete the readMsgTask thread
        while(mRunRecvTask)
        {
            this_thread::sleep_for(chrono::milliseconds(200));

            char buffer[BUFF_SIZE];
            int msgLn = mSocketComm.readFromSocket(buffer, sizeof(buffer));
            if(msgLn<=0)
            {
                continue;
            }
            unique_ptr<char[]> upMsgBytes{new char[msgLn]};
            for(int i=0; i<msgLn; i++)
            {
                upMsgBytes[i] = buffer[i];
            }
            unique_ptr<ChatMessage> upChatMsg = mChatMessageFactory.getChatMessage(upMsgBytes[0]);
            upChatMsg->decodeMessage(move(upMsgBytes));

            {
                lock_guard<mutex> lock(mReceiveMux);
                if (upChatMsg != nullptr) 
                {
                    mReceiveQueue.push(move(upChatMsg));
                }
            }

        }

        Logger::log(INFO, "readMsgTask end");
    };


    mSendThread = thread(sendMsgTask);
    mReceiveThread = thread(readMsgTask);
}

/**
 * @brief Close the transport and stop read/write threads
 */
bool MessageTransport::close()
{
    mRunSendTask = false;
    mRunRecvTask = false;
    mSendThread.join();
    mReceiveThread.join();
    mSocketComm.closeComm();

    return true;
}