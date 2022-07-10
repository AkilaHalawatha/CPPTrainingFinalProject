#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

/**
 * @brief  Definition of the ChatMessage class
 * @author Akila Halawatha
 */

#include <memory>

/**
 * @brief ChatMessage abstract class will be inherited by all message types
 */
class ChatMessage
{
public:
    /**
     * @brief Abstract function to acquire parameters of the ChatMessage
     *
     * @return None
     */
    virtual void acquireMessageParams() = 0;

    /**
     * @brief Abstract function to encode a ChatMessage into a byte stream
     *
     * @return Unique pointer to the byte stream
     */
    virtual std::unique_ptr<char[]> encodeMessage()= 0;

    /**
     * @brief Abstract function to decode a byte stream into a ChatMessage
     * @param[in]  upChatMsg              Unique pointer of the byte stream
     *
     * @return None
     */
    virtual void decodeMessage(std::unique_ptr<char[]> upMsgBytes)= 0;

    /**
     * @brief Abstract function to display the ChatMessage
     *
     * @return None
     */
    virtual void displayMessage() = 0;

    /**
     * @brief Static function to fill the data length of the byte stream
     * @param[in]  uprMsgBytes             Unique pointer reference of the byte stream
     * @param[in]  dataLn                  data length
     *
     * @return None
     */
    static void fillDataLenBytes(std::unique_ptr<char[]>& uprMsgBytes, int dataLn);

    /**
     * @brief Static function to get the data length from the byte stream
     * @param[in]  uprMsgBytes             Unique pointer reference of the byte stream
     *
     * @return Data length from the byte stream
     */
    static int getDataLen(std::unique_ptr<char[]>& uprMsgBytes);

    static const int MSG_TYPE_IDX = 0;
    static const int MSG_TYPE_LEN = 1;

    static const int MSG_LEN_IDX = MSG_TYPE_IDX + MSG_TYPE_LEN;
    static const int MSG_LEN_LEN = 4;

    static const int MSG_DATA_IDX = MSG_LEN_IDX + MSG_LEN_LEN;
    static const int MSG_HEADER_LEN = MSG_TYPE_LEN + MSG_LEN_LEN;
};

#endif // CHAT_MESSAGE_H