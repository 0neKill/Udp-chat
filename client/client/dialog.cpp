#include "dialog.h"
#include "ui_dialog.h"



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->systemTray = new QSystemTrayIcon(this);
    this->systemTray->setIcon(QIcon(":/myicon.png"));
    this->systemTray->setVisible(true);
}

void Dialog::initialSocket(int port, int serverPort)
{
    this->serverPort =serverPort;
    this->socket  = new QUdpSocket(this);
    this->socket->bind(QHostAddress::LocalHost, quint16(port));
    connect(this->socket, &QUdpSocket::readyRead, this, &Dialog::readPendingDatagram);
    this->sendDatagram("connect");
}

void Dialog::readPendingDatagram(){
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    while(this->socket->hasPendingDatagrams()) {
        datagram.resize(int(this->socket->pendingDatagramSize()));
        this->socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        this->ui->viewMessage->append(datagram);
        this->systemTray->showMessage("Новое сообщение",QString(datagram));
    }
}

void Dialog::sendDatagram(QString message){
    this->socket->writeDatagram(message.toUtf8(), QHostAddress::LocalHost, quint16(this->serverPort));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_sendButton_clicked()
{
    if(!this->isMessage()) {
        return;
    }
    QString message = this->ui->inputMessage->text();
    this->sendDatagram(message);
    this->ui->viewMessage->append("<font color=#990012>Вы: "+ message +"  ("+this->dt+")"+"</font>");
    this->ui->inputMessage->clear();
}

bool Dialog::isMessage() {
    QString message = this->ui->inputMessage->text();
    if(message == "") {
        return false;
    }
    return true;
}
