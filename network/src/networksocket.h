#ifndef NETWORKSOCKET_H
#define NETWORKSOCKET_H

#include "networkdata.h"
#include <QtNetwork/QTcpSocket>

class NetworkSocket : public QObject {
    Q_OBJECT
public:
    explicit NetworkSocket(QTcpSocket* socket, QObject* parent = nullptr);

    /**
     * @brief Send data to host server
     */
    void send(NetworkData);

    /**
     * @brief Connect to a host server
     * @param host hostname, IP or domain name
     * @param port port number to connect
     */
    void hello(const QString& host, quint16 port);

    /**
     * @brief Get the base TCP socket for signal connection
     */
    QTcpSocket* base() const;

private:
    QTcpSocket* socket;

signals:
    /**
     * @brief Signal emitted when received data from server
     */
    void receive(NetworkData);

    /**
     * @brief Signal emitted when message received is invalid
     */
    void parseError(const InvalidMessage&);

public slots:
    /**
     * @brief Close current connection
     */
    void bye();

private slots:
    /**
     * @brief Connected to QTcpSocket for parsing data transmitted
     */
    void receiveData();
};

#endif // NETWORKSOCKET_H
