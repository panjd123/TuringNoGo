#include "networksocket.h"
#include <QtCore>

NetworkSocket::NetworkSocket(QTcpSocket* socket, QObject* parent)
    : QObject(parent)
    , socket(socket) {
    this->socket->setParent(this);
    connect(this->base(), &QAbstractSocket::readyRead, this, &NetworkSocket::receiveData);
}

QTcpSocket* NetworkSocket::base() const {
    return this->socket;
}

void NetworkSocket::hello(const QString& host, quint16 port) {
    this->socket->abort();
    this->socket->connectToHost(host, port);
}

void NetworkSocket::bye() {
    this->socket->disconnectFromHost();
}

void NetworkSocket::receiveData() {
    auto whole_block = this->socket->readAll();
    auto blocks = whole_block.split('\n');
    for (const auto& block : blocks) {
        try {
            NetworkData recv(block);
            qDebug() << "Client: "
                     << static_cast<int>(recv.op) 
                     << ' ' << recv.data1 << ' ' << recv.data2 << Qt::endl;
            emit receive(recv);
        }
        catch (const InvalidMessage& e) {
            if (!e.messageReceived().isEmpty()) {
                emit parseError(e);
            }
        }
    }
}

void NetworkSocket::send(NetworkData data) {
    this->socket->write(data.encode());
    this->socket->flush();
}
