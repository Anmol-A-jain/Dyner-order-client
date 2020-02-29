#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QObject>

class serverSocket : public QObject
{
public:
    serverSocket(QWidget* parent);
    void connectToSerever(QString ip);
    static QTcpSocket* serverClient;
    static QByteArray setAction(int action,QByteArray data);

public slots:
    void myReadReady();

    void myConnected();

    void myDisconnect();


private:
    QWidget* myParent;
};

#endif // SERVERSOCKET_H
