#ifndef SERVER_H
#define SERVER_H

#include "socket.h"

#include <QDialog>
#include <QUdpSocket>

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();
    time_t now = time(0);
    char *dt = ctime(&now);

private:
    Ui::Server *ui;
    QUdpSocket *socket;
    QList<Socket*> sockets;

public:
    void initialSocket(int port);
    void readPendingDatagrams();
    void sendDatagram(QString message, int port);
    void sendMessageAllSockets(QString message, int port);
    void sendMessageAllSockets(QString message);
    void saveToFile(QString message);
    bool isMessage();
    bool isSocketEmpty(quint16 senderPort);

private slots:
    void on_sendButton_clicked();

};

#endif // SERVER_H
