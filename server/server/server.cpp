#include "server.h"
#include "ui_server.h"

#include <QFile>

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
}

Server::~Server()
{
    delete ui;
}

void Server::initialSocket(int port){
    this->socket = new QUdpSocket(this);
    this->socket->bind(QHostAddress::Any, quint16(port));
    connect(this->socket, &QUdpSocket::readyRead, this, &Server::readPendingDatagrams);
}


void Server::readPendingDatagrams(){
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    while(this->socket->hasPendingDatagrams()) {
        datagram.resize(int(this->socket->pendingDatagramSize()));
        this->socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        if(!this->isSocketEmpty(senderPort)){
            this->sockets.append(new Socket(senderPort));
        } else {
            this->sendMessageAllSockets(datagram, senderPort);
        }
        this->ui->viewMessage->append("<font color=green>"+QString("%1").arg(senderPort)+": "+QString(datagram)+"  ("+this->dt+")</font>");
    }
}

void Server::sendDatagram(QString message,int port){
    QString messageSend = "<font color=green>"+message+"</font>";
    this->socket->writeDatagram(messageSend.toUtf8(), QHostAddress::LocalHost, quint16(port));
}

void Server::saveToFile(QString message){
    QFile file("belyakov.txt");
    if(file.open(QIODevice::Append)) {
        QTextStream out(&file);
        out << message+"\n";
    }
    file.close();
}

void Server::sendMessageAllSockets(QString message, int port) {
    QString messageSend = QString("%1").arg(port)+": "+QString(message)+"  ("+this->dt+")";
    this->saveToFile(messageSend);
    for(Socket *socket: this->sockets) {
        if(socket->equals(port)) {
            continue;
        }
      this->sendDatagram(messageSend, socket->port);
    }
}

void Server::sendMessageAllSockets(QString message) {
    QString messageSend ="SERVER: "+QString(message)+"  ("+this->dt+")";
    this->saveToFile(messageSend);
    for(Socket *socket: this->sockets) {
      this->sendDatagram(messageSend, socket->port);
    }
}

bool Server::isSocketEmpty(quint16 senderPort) {
    for(Socket *socket: this->sockets) {
        if(socket->equals(senderPort)) {
            return true;
        }
    }
    return false;
}

void Server::on_sendButton_clicked()
{
    if(!this->isMessage()) {
        return;
    }
    QString message = this->ui->inputMessage->text();
    this->sendMessageAllSockets(message);
    this->ui->viewMessage->append("<font color=#990012>Вы: "+ message +"  ("+this->dt+")"+"</font>");
    this->ui->inputMessage->clear();
}

bool Server::isMessage() {
    QString message = this->ui->inputMessage->text();
    if(message == "") {
        return false;
    }
    return true;
}
