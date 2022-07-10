#ifndef FILE_CHAT_MESSAGE_H
#define FILE_CHAT_MESSAGE_H

/**
 * @brief  Definition of the FileChatMessage class
 * @author Akila Halawatha
 */

#include "ChatMessage.h"
#include <string>

/**
 * @brief Concrete class FileChatMessage inherits from ChatMessage
 */
class FileChatMessage : public ChatMessage
{
public:
    /**
     * @brief Acquire parameters of the FileChatMessage
     *
     * @return None
     */
    void acquireMessageParams();

    /**
     * @brief Static function to get the message type
     *
     * @return Message type
     */
    static char getMessageType();

    /**
     * @brief Encode a FileChatMessage into a byte stream
     *
     * @return Unique pointer to the byte stream
     */
    std::unique_ptr<char[]> encodeMessage();

    /**
     * @brief Decode a byte stream into a FileChatMessage
     * @param[in]  upChatMsg              Unique pointer of the byte stream
     *
     * @return None
     */
    void decodeMessage(std::unique_ptr<char[]> upMsgBytes);

    /**
     * @brief Display the FileChatMessage
     *
     * @return None
     */
    void displayMessage();
private:
    std::string mFilePath = "";
    const static char m_MESSAGE_TYPE = 2;
};

#endif // FILE_CHAT_MESSAGE_H