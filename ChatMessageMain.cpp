/**
 * @brief  Implementation of the chat app main
 * @author Akila Halawatha
 */

#include "ChatMessageFactory.h"
#include "ChatMessage.h"
#include "MessageTransport.h"
#include "Logger.h"

/**
 * @brief Chat app main method
 *
 * @return Status
 */
int main()
{
    char buffer[1024] = { 0 };
    int msgLn = 0;
    ChatMessageFactory chatMessageFactory;
    Logger::setLogLevel(INFO);
    MessageTransport messageTransport;

    messageTransport.serverListen();
    messageTransport.runSendRecvTasks();

    // Receive from the client
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::unique_ptr<ChatMessage> chatMessageRecv = messageTransport.getMessageFromQueue();
    if(chatMessageRecv != nullptr)
    {
        chatMessageRecv->displayMessage();
    }

    // Send to the client
    std::unique_ptr<ChatMessage> chatMessageSend = chatMessageFactory.getChatMessage(1);
    chatMessageSend->acquireMessageParams();
    messageTransport.sendMessageToQueue(std::move(chatMessageSend));

    messageTransport.close();

    
    /*messageTransport.clientConnect();
    messageTransport.runSendRecvTasks();

    // Send to the server
    // Queue test
    std::unique_ptr<ChatMessage> chatMessageSend = chatMessageFactory.getChatMessage(3);
    chatMessageSend->acquireMessageParams();
    messageTransport.sendMessageToQueue(std::move(chatMessageSend));
    

    // Receive from the server
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    std::unique_ptr<ChatMessage> chatMessageRecv = messageTransport.getMessageFromQueue();
    if(chatMessageRecv != nullptr)
    {
        chatMessageRecv->displayMessage();
    }

    messageTransport.close();*/


    return 0;
}