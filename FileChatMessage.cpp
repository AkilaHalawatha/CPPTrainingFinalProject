/**
 * @brief  Implementation of the FileChatMessage class
 * @author Akila Halawatha
 */

#include "Logger.h"
#include "FileChatMessage.h"

using namespace std;

// TODO : Implement all functions for FileChatMessage

/**
 * @brief Acquire parameters of the FileChatMessage
 *
 * @return None
 */
void FileChatMessage::acquireMessageParams()
{
    mFilePath = "/home/akilahalawatha/CppTraining/test.txt";
}

/**
 * @brief Static function to get the message type
 *
 * @return Message type
 */
char FileChatMessage::getMessageType()
{
    return m_MESSAGE_TYPE;
}

/**
 * @brief Encode a FileChatMessage into a byte stream
 *
 * @return Unique pointer to the byte stream
 */
unique_ptr<char[]> FileChatMessage::encodeMessage()
{

    return nullptr;
}

/**
 * @brief Decode a byte stream into a FileChatMessage
 * @param[in]  upChatMsg              Unique pointer of the byte stream
 *
 * @return None
 */
void FileChatMessage::decodeMessage(unique_ptr<char[]> upMsgBytes)
{
    
}

/**
 * @brief Display the FileChatMessage
 *
 * @return None
 */
void FileChatMessage::displayMessage()
{
    Logger::log(NONE, mFilePath);
}

