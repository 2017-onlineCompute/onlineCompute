#include "clientdialog.h"
#include "ui_clientdialog.h"
#include <QDebug>

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
    qDebug()<< buf;
    sock.write_some(buffer(buf));

    char result[BUFSIZE];
    sock.read_some(buffer(result));
    QString res = QString(QLatin1String(result));

    (ui->resultEdit)->setText(res);
    qDebug()<< (ui->resultEdit)->text();

}

void ClientDialog::enableOkButton(const QString &text)
{
    (ui->okButton)->setEnabled(!text.isEmpty());
}
