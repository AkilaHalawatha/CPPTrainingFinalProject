/**
 * @brief  Implementation of the ChatMessage class
 * @author Akila Halawatha
 */

#include "Logger.h"
#include "ChatMessage.h"

using namespace std;

/**
 * @brief Static function to fill the data length of the byte stream
 * @param[in]  uprMsgBytes             Unique pointer reference of the byte stream
 * @param[in]  dataLn                  data length
 *
 * @return None
 */
void ChatMessage::fillDataLenBytes(unique_ptr<char[]>& uprMsgBytes, int dataLn)
{
    uprMsgBytes[MSG_LEN_IDX]   = (dataLn & 0xFF);
    uprMsgBytes[MSG_LEN_IDX+1] = ((dataLn >> 8) & 0xFF);
    uprMsgBytes[MSG_LEN_IDX+2] = ((dataLn >> 16) & 0xFF);
    uprMsgBytes[MSG_LEN_IDX+3] = ((dataLn >> 24) & 0xFF);
}

/**
 * @brief Static function to get the data length from the byte stream
 * @param[in]  uprMsgBytes             Unique pointer reference of the byte stream
 *
 * @return Data length from the byte stream
 */
int ChatMessage::getDataLen(unique_ptr<char[]>& uprMsgBytes)
{
    int dataLn;

    dataLn  = uprMsgBytes[MSG_LEN_IDX];
    dataLn |= (uprMsgBytes[MSG_LEN_IDX+1] << 8);
    dataLn |= (uprMsgBytes[MSG_LEN_IDX+1] << 16);
    dataLn |= (uprMsgBytes[MSG_LEN_IDX+1] << 24);

    return dataLn;
}