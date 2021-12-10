#include "server.h"
#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_startButton_clicked()
{
    if(!this->isPortExists()) {
        QMessageBox::warning(this,"Ошибка","Введите любой port");
        return;
    }

    if(!this->isPortNumeric()) {
        QMessageBox::warning(this,"Ошибка","Введенный порт не является числом" );
        return;
    }
    const int port = this->ui->inputPort->text().toInt();
    Server *server = new Server();
    server->show();
    server->initialSocket(port);
    this->close();
}

bool ServerWindow::isPortExists(){
    if(this->ui->inputPort->text() != "") {
        return true;
    }
    return false;
}

bool ServerWindow::isPortNumeric(){
   return this->ui->inputPort->text().toInt();
}
