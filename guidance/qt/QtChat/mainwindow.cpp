#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // display welcome infomation
    ui->chatHistoryEdit->appendPlainText(QString("欢迎进入聊天室\n"));
    // read only
    ui->chatHistoryEdit->setReadOnly(true);
    // 焦点移到发送框中
    ui->chatEdit->setFocus();

    this->usernameEdit = new QLineEdit(this);
    this->usernameEdit->setGeometry(10,ui->chatEdit->y(),61,21);
    this->usernameEdit->setText(QString("张三"));
    this->usernameEdit->show();
    qDebug()<<this->usernameEdit->geometry() << " "<< this->ui->chatEdit->geometry();

    // 信号槽
    connect(this->ui->sendButton,&QPushButton::clicked,this,&MainWindow::send);
}

bool MainWindow::send(){
    QString text = this->ui->chatEdit->text();
    QString username = this->usernameEdit->text();
    QDateTime current;
    QString time = current.currentDateTime().toString("MMM dd hh:mm::ss");
    QString data = time + " " + username + "\t" + text;
    this->ui->chatEdit->setText("");
    if(text == ""){
        return false;
    }
    qDebug()<<data;
    this->ui->chatHistoryEdit->appendPlainText(data+"\n");
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

