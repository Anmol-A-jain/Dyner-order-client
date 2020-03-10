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
    static QString setAction(int action,QByteArray data);

public slots:
    void myReadReady();

    void myConnected();

    void myDisconnect();


private:
    QWidget* myParent;
    qint16 tblNo;
};

#endif // SERVERSOCKET_H
