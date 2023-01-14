#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QtCore>

enum class OPCODE : int {
    READY_OP = 200000,
    REJECT_OP,
    MOVE_OP,
    GIVEUP_OP,
    TIMEOUT_END_OP,
    SUICIDE_END_OP,
    GIVEUP_END_OP,
    LEAVE_OP,
    CHAT_OP,
};

class InvalidMessage : public QException {
public:
    InvalidMessage() = delete;
    InvalidMessage(QByteArray message);

    /**
     * @brief Get the message which can't be parsed
     * @return Message as QByteArray
     */
    QByteArray messageReceived() const;

private:
    QByteArray message;
};

/**
 * @brief Data structure for standard messages defined by protocol
 */
class NetworkData {
public:
    NetworkData() = delete;

    /**
     * @brief NetworkData constructor from operation id and data strings
     * @param op Operation ID
     * @param data1 First parameter string of the operation
     * @param data2 Second parameter string of the operation
     */
    NetworkData(OPCODE op, QString data1, QString data2);

    /**
     * @brief NetworkData constructor from message received
     * @param message The message received byte block for parsing
     * @exception InvalidMessage Thrown if failed to parse the byte block
     */
    NetworkData(QByteArray message);

    OPCODE op;
    QString data1;
    QString data2;

    /**
     * @brief Encode the data to QByteArray for sending
     */
    QByteArray encode();
};

#endif // NETWORKDATA_H
