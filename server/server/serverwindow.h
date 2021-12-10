#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private slots:
    void on_startButton_clicked();
    bool isPortExists();
    bool isPortNumeric();

private:
    Ui::ServerWindow *ui;
};

#endif // SERVERWINDOW_H
