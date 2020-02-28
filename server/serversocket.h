#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QObject>

class serverSocket : public QObject
{
public:
    serverSocket();
    void connectToSerever(QString ip);
    static QTcpSocket* serverClient;
    void setAction(int action,QByteArray data);

public slots:
    void myReadReady();

    void myConnected();


private:
};

#endif // SERVERSOCKET_H
