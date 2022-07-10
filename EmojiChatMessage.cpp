/**
 * @brief  Implementation of the EmojiChatMessage class
 * @author Akila Halawatha
 */

#include "Logger.h"
#include "EmojiChatMessage.h"

using namespace std;

/**
 * @brief Acquire parameters of the EmojiChatMessage
 *
 * @return None
 */
void EmojiChatMessage::acquireMessageParams()
{
    // TODO : Implement this
    Logger::log(NONE, Emoji::getEmojiList());
    mEmoji = Emoji(0);
}

/**
 * @brief Static function to get the message type
 *
 * @return Message type
 */
char EmojiChatMessage::getMessageType()
{
    return m_MESSAGE_TYPE;
}

/**
 * @brief Encode a EmojiChatMessage into a byte stream
 *
 * @return Unique pointer to the byte stream
 */
unique_ptr<char[]> EmojiChatMessage::encodeMessage()
{
    int msgDataLn  = sizeof(char);
    int msgLn = msgDataLn + MSG_HEADER_LEN;
    unique_ptr<char[]> upMsgBytes{new char[msgLn]};

    upMsgBytes[MSG_TYPE_IDX] = m_MESSAGE_TYPE;
    fillDataLenBytes(upMsgBytes, msgDataLn);
    upMsgBytes[MSG_DATA_IDX] = mEmoji.getEmojiIdx();

    return upMsgBytes;
}

/**
 * @brief Decode a byte stream into a EmojiChatMessage
 * @param[in]  upChatMsg              Unique pointer of the byte stream
 *
 * @return None
 */
void EmojiChatMessage::decodeMessage(unique_ptr<char[]> upMsgBytes)
{
    int msgDataLn = getDataLen(upMsgBytes);
    if(msgDataLn == sizeof(char))
    {
        mEmoji = Emoji(upMsgBytes[MSG_DATA_IDX]);
    }
    else
    {
        mEmoji = Emoji(0);
    }
}

/**
 * @brief Display the EmojiChatMessage
 *
 * @return None
 */
void EmojiChatMessage::displayMessage()
{
    Logger::log(NONE, mEmoji.getEmojiSymbol());
}
