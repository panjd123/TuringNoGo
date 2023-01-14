#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include "networkdata.h"
#include <QtNetwork>

class NetworkServer : public QTcpServer {
    Q_OBJECT
public:
    explicit NetworkServer(QObject* parent = nullptr);

    void send(QTcpSocket* client, NetworkData data);

signals:
    void receive(QTcpSocket* client, NetworkData data);
    void parseError(const InvalidMessage&);
    void leave(QTcpSocket*);

private slots:
    void receiveData(QObject*);
    void disconnect(QObject*);
    void newconnection();

private:
    QList<QTcpSocket*> clients;
    QSignalMapper* disconnMapper;
    QSignalMapper* recvMapper;
};

#endif // NETWORKSERVER_H
