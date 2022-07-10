#ifndef EMOJI_CHAT_MESSAGE_H
#define EMOJI_CHAT_MESSAGE_H

/**
 * @brief  Definition of the EmojiChatMessage class
 * @author Akila Halawatha
 */

#include "ChatMessage.h"
#include "Emoji.h"

/**
 * @brief Concrete class EmojiChatMessage inherits from ChatMessage
 */
class EmojiChatMessage : public ChatMessage
{
public:
    /**
     * @brief Acquire parameters of the EmojiChatMessage
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
     * @brief Encode a EmojiChatMessage into a byte stream
     *
     * @return Unique pointer to the byte stream
     */
    std::unique_ptr<char[]> encodeMessage();

    /**
     * @brief Decode a byte stream into a EmojiChatMessage
     * @param[in]  upChatMsg              Unique pointer of the byte stream
     *
     * @return None
     */
    void decodeMessage(std::unique_ptr<char[]> upMsgBytes);

    /**
     * @brief Display the EmojiChatMessage
     *
     * @return None
     */
    void displayMessage();
private:
    Emoji mEmoji = Emoji(0);
    const static char m_MESSAGE_TYPE = 3;
};

#endif // EMOJI_CHAT_MESSAGE_H