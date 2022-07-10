#ifndef EMOJI_H
#define EMOJI_H

/**
 * @brief  Definition of the Emoji class
 * @author Akila Halawatha
 */

#include <string>

/**
 * @brief Details of the emoji
 */
class Emoji
{
public:
    /**
     * @brief Crete an emoji from index
     * @param[in]  upChatMsg              Emoji index from m_EMOJI_LIST
     */
    Emoji(int emojiIdx);

    /**
     * @brief Static function to get the emoji list
     *
     * @return Emoji list
     */
    static std::string getEmojiList();

    /**
     * @brief Get the emoji index
     *
     * @return Index of the emoji from m_EMOJI_LIST 
     */
    int getEmojiIdx();

    /**
     * @brief Get the emoji symbol
     *
     * @return Emoji symbol from m_EMOJI_LIST 
     */
    std::string getEmojiSymbol();
private:
    int mEmojiIdx = 0;
    const static std::string m_EMOJI_LIST[];
};

#endif // EMOJI_H