#include "clientdialog.h"
#include "ui_clientdialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#define BUFSIZE 1024

using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace boost::asio;

io_service service;
ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"),2001);
ip::tcp::socket sock(service);


ClientDialog::ClientDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    sock.connect(ep);

    char readbuf[512];
    sock.read_some(buffer(readbuf));
    QString notice = QString(QLatin1String(readbuf));
    QMessageBox::warning(this,tr("Notice"),notice,QMessageBox::Yes);
    connect(ui->inputEdit,&QLineEdit::textChanged, this,&ClientDialog::enableOkButton);
    connect(ui->okButton, &QPushButton::clicked,this, &ClientDialog::okClicked);
    connect(ui->resultEdit,&QLineEdit::textEdited,this,&ClientDialog::enableOkButton);
    connect(ui->closeButton, &QPushButton::clicked, this, &ClientDialog::close);
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

void ClientDialog::okClicked()
{
    QString text = (ui->inputEdit)->text();

    char buf[BUFSIZE];

    strcpy(buf,text.toLocal8Bit().data());
    sock.write_some(buffer(buf));

    char readResult[BUFSIZE];
    sock.read_some(buffer(readResult));
    double result = atof(readResult);
    QString res = QString::number(result);
    (ui->resultEdit)->setText(res);

}

void ClientDialog::enableOkButton(const QString &text)
{
    (ui->okButton)->setEnabled(!text.isEmpty());
}
