/**
 * @brief  Implementation of the Emoji class
 * @author Akila Halawatha
 */

#include "Logger.h"
#include "Emoji.h"

using namespace std;

const string Emoji::m_EMOJI_LIST[] =
{  
    ":)",  // Smile
    ":(",  // Frown
    ":P",  // Tongue
    ":D",  // Grin
    ":O",  // Gasp

};

/**
 * @brief Crete an emoji from index
 * @param[in]  upChatMsg              Emoji index from m_EMOJI_LIST
 */
Emoji::Emoji(int emojiIdx)
{
    int emojiListSize = sizeof(m_EMOJI_LIST)/sizeof(m_EMOJI_LIST[0]);
    if((emojiIdx >= 0) && (emojiIdx < emojiListSize))
    {
        mEmojiIdx = emojiIdx;
    }
    else
    {
        mEmojiIdx = 0;
    }
}

/**
 * @brief Static function to get the emoji list
 *
 * @return Emoji list
 */
string Emoji::getEmojiList()
{
    string ret = "";
    int emojiListSize = sizeof(m_EMOJI_LIST)/sizeof(m_EMOJI_LIST[0]);

    for(int i=0; i<emojiListSize; i++)
    {
        ret += to_string(i+1) + " - " + m_EMOJI_LIST[i] + "\n";
    }

    return ret;
}

/**
 * @brief Get the emoji index
 *
 * @return Index of the emoji from m_EMOJI_LIST 
 */
int Emoji::getEmojiIdx()
{
   return mEmojiIdx;
}

/**
 * @brief Get the emoji symbol
 *
 * @return Emoji symbol from m_EMOJI_LIST 
 */
string Emoji::getEmojiSymbol()
{
   return m_EMOJI_LIST[mEmojiIdx];
}
