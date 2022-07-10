#ifndef TEXT_CHAT_MESSAGE_H
#define TEXT_CHAT_MESSAGE_H

/**
 * @brief  Definition of the TextChatMessage class
 * @author Akila Halawatha
 */

#include "ChatMessage.h"
#include <string>

/**
 * @brief Concrete class TextChatMessage inherits from ChatMessage
 */
class TextChatMessage : public ChatMessage
{
public:
    /**
     * @brief Acquire parameters of the TextChatMessage
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
     * @brief Encode a TextChatMessage into a byte stream
     *
     * @return Unique pointer to the byte stream
     */
    std::unique_ptr<char[]> encodeMessage();

    /**
     * @brief Decode a byte stream into a TextChatMessage
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
    std::string mTextMessage = "";
    const static char m_MESSAGE_TYPE = 1;

    /**
     * @brief Fill message data in a TextChatMessage
     * @param[in]  upChatMsg              Unique pointer reference of the byte stream
     * @param[in]  msgDataLn              Message data length
     *
     * @return None
     */
    void fillTextMessageData(std::unique_ptr<char[]>& upMsgBytes, int msgDataLn);

    /**
     * @brief Get message data from a TextChatMessage
     * @param[in]  upChatMsg              Unique pointer reference of the byte stream
     * @param[in]  msgDataLn              Message data length
     *
     * @return None
     */
    void getTextMessageData(std::unique_ptr<char[]>& upMsgBytes, int msgDataLn);
};

#endif // TEXT_CHAT_MESSAGE_H