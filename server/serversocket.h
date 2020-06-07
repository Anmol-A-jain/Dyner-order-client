#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QObject>

class serverSocket : public QObject
{
    Q_OBJECT
public:
    serverSocket(QWidget* parent);
    void connectToSerever(QString ip);
    static QTcpSocket* serverClient;

    ~serverSocket();

public slots:
    void myReadReady();

    void myConnected();

    void myDisconnect();

signals:
    void dinningTableList(int);


private:
    QWidget* myParent;
};

#endif // SERVERSOCKET_H
