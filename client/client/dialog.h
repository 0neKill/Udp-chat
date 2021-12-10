#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QUdpSocket>
#include <QSystemTrayIcon>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    time_t now = time(0);
    char *dt = ctime(&now);
    int serverPort;

public slots:
    void initialSocket(int port, int serverPort);
    void readPendingDatagram();
    void sendDatagram(QString message);
private slots:
    void on_sendButton_clicked();
    bool isMessage();

private:
    Ui::Dialog *ui;
    QUdpSocket *socket;
    QSystemTrayIcon *systemTray;
};

#endif // DIALOG_H
