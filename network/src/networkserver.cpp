#include "networkserver.h"

NetworkServer::NetworkServer(QObject* parent)
    : QTcpServer(parent)
    , disconnMapper(new QSignalMapper(this))
    , recvMapper(new QSignalMapper(this)) {
    connect(this, &QTcpServer::newConnection, this, &NetworkServer::newconnection);
    connect(this->disconnMapper, &QSignalMapper::mappedObject, this, &NetworkServer::disconnect);
    connect(this->recvMapper, &QSignalMapper::mappedObject, this, &NetworkServer::receiveData);
}

void NetworkServer::receiveData(QObject* obj) {
    QTcpSocket* client = dynamic_cast<QTcpSocket*>(obj);
    Q_ASSERT(client != nullptr);
    QByteArray whole_block = client->readAll();
    QList<QByteArray> blocks = whole_block.split('\n');
    for (const auto& block : blocks) {
        if (block.isEmpty())
            continue;
        try {
            NetworkData data(block);
            qDebug() << "Server: "
                     << static_cast<int>(data.op) 
                     << ' ' << data.data1 << ' ' << data.data2 << Qt::endl;
            emit receive(client, data);
        }
        catch (const InvalidMessage& m) {
            emit parseError(m);
        }
    }
}

void NetworkServer::send(QTcpSocket* client, NetworkData data) {
    qDebug() << "send " 
             << static_cast<int>(data.op) 
             << data.data1 << data.data2 << Qt::endl;
    client->write(data.encode());
    client->flush();
}

void NetworkServer::disconnect(QObject* client) {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if (*it == client) {
            emit leave(*it);
            clients.erase(it);
            break;
        }
    }
}

void NetworkServer::newconnection() {
    QTcpSocket* client = this->nextPendingConnection();
    clients.append(client);
    connect(client, &QIODevice::readyRead, this->recvMapper, qOverload<>(&QSignalMapper::map));
    connect(client, &QAbstractSocket::disconnected, this->disconnMapper, qOverload<>(&QSignalMapper::map));
    this->disconnMapper->setMapping(client, client);
    this->recvMapper->setMapping(client, client);
}
