#include "dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_startButton_clicked()
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
    const int serverPort = this->ui->inputServerPort->text().toInt();
    Dialog *dialog = new Dialog();
    dialog->show();
    dialog->initialSocket(port, serverPort);
    this->close();

}

bool MainWindow::isPortExists(){
    if(this->ui->inputPort->text() != "" && this->ui->inputServerPort->text() != "") {
        return true;
    }
    return false;
}

bool MainWindow::isPortNumeric(){
   return this->ui->inputPort->text().toInt() && this->ui->inputServerPort->text().toInt();
}
