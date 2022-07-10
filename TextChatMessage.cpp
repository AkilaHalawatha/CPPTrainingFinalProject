/**
 * @brief  Implementation of the TextChatMessage class
 * @author Akila Halawatha
 */

#include "Logger.h"
#include "TextChatMessage.h"

using namespace std;

/**
 * @brief Acquire parameters of the TextChatMessage
 *
 * @return None
 */
void TextChatMessage::acquireMessageParams()
{
    // TODO : Implement this
    mTextMessage = "This is a test";
}

/**
 * @brief Static function to get the message type
 *
 * @return Message type
 */
char TextChatMessage::getMessageType()
{
    return m_MESSAGE_TYPE;
}

/**
 * @brief Encode a TextChatMessage into a byte stream
 *
 * @return Unique pointer to the byte stream
 */
unique_ptr<char[]> TextChatMessage::encodeMessage()
{
    int msgDataLn  = mTextMessage.length();
    int msgLn = msgDataLn + MSG_HEADER_LEN;
    unique_ptr<char[]> upMsgBytes{new char[msgLn]};

    upMsgBytes[MSG_TYPE_IDX] = m_MESSAGE_TYPE;
    fillDataLenBytes(upMsgBytes, msgDataLn);
    fillTextMessageData(upMsgBytes, msgDataLn);

    return upMsgBytes;
}

/**
 * @brief Decode a byte stream into a TextChatMessage
 * @param[in]  upChatMsg              Unique pointer of the byte stream
 *
 * @return None
 */
void TextChatMessage::decodeMessage(unique_ptr<char[]> upMsgBytes)
{
    int msgDataLn = getDataLen(upMsgBytes);
    getTextMessageData(upMsgBytes, msgDataLn);
}

/**
 * @brief Display the FileChatMessage
 *
 * @return None
 */
void TextChatMessage::displayMessage()
{
    Logger::log(NONE, mTextMessage);
}

/**
 * @brief Fill message data in a TextChatMessage
 * @param[in]  upChatMsg              Unique pointer reference of the byte stream
 * @param[in]  msgDataLn              Message data length
 *
 * @return None
 */
void TextChatMessage::fillTextMessageData(unique_ptr<char[]>& uprMsgBytes, int msgDataLn)
{
    for(int i=0; i<msgDataLn; i++)
    {
        uprMsgBytes[MSG_DATA_IDX + i] = mTextMessage[i];
    }
}

/**
 * @brief Get message data from a TextChatMessage
 * @param[in]  upChatMsg              Unique pointer reference of the byte stream
 * @param[in]  msgDataLn              Message data length
 *
 * @return None
 */
void TextChatMessage::getTextMessageData(unique_ptr<char[]>& uprMsgBytes, int msgDataLn)
{
    mTextMessage = "";

    for(int i=0; i<msgDataLn; i++)
    {
        mTextMessage.push_back(uprMsgBytes[MSG_DATA_IDX + i]);
    }
}

