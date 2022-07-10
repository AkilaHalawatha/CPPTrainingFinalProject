#ifndef CHAT_MESSAGE_FACTORY_H
#define CHAT_MESSAGE_FACTORY_H

/**
 * @brief  Definition of the ChatMessageFactory class
 * @author Akila Halawatha
 */

#include "ChatMessage.h"

/**
 * @brief Factory class for all ChatMessage types
 */
class ChatMessageFactory
{
public:
    /**
     * @brief Generate a ChatMessage unique pointer from the message type
     * @param[in]  msgType                Message type
     *
     * @return Unique pointer to the ChatMessage
     */
    std::unique_ptr<ChatMessage> getChatMessage(char msgType);

    /**
     * @brief Display all available message types
     *
     * @return None
     */
    void displayAllMessageTypes();
private:
};

#endif // CHAT_MESSAGE_FACTORY_H