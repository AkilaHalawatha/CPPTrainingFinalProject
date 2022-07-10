/**
 * @brief  Implementation of the ChatMessageFactory class
 * @author Akila Halawatha
 */

#include "ChatMessageFactory.h"
#include "TextChatMessage.h"
#include "FileChatMessage.h"
#include "EmojiChatMessage.h"

using namespace std;

/**
 * @brief Generate a ChatMessage unique pointer from the message type
 * @param[in]  msgType                Message type
 *
 * @return Unique pointer to the ChatMessage
 */
unique_ptr<ChatMessage> ChatMessageFactory::getChatMessage(char msgType)
{
    if (msgType == TextChatMessage::getMessageType())
    {
        return make_unique<TextChatMessage>();
    }
    else if (msgType == FileChatMessage::getMessageType())
    {
        return make_unique<FileChatMessage>();
    }
    else if (msgType == EmojiChatMessage::getMessageType())
    {
        return make_unique<EmojiChatMessage>();
    }
    else
    {
        return nullptr;
    }
    
}

/**
 * @brief Display all available message types
 *
 * @return None
 */
void ChatMessageFactory::displayAllMessageTypes()
{
    // TODO : Implement this
}


