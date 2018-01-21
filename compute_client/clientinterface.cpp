#include "clientinterface.h"
#include "ui_clientinterface.h"
#include "registeinterface.h"
#include "ui_clientinterface.h"
#include "clientdialog.h"
#include "ui_clientdialog.h"
#include <iostream>
#include "database.h"
#include <QMessageBox>


Clientinterface::Clientinterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clientinterface)
{

    ui->setupUi(this);
    (ui->passwordLine)->setEchoMode(QLineEdit::Password);
//    connect(ui->okButton,&QPushButton::clicked,this,&Clientinterface::on_okButton_clicked);
}

Clientinterface::~Clientinterface()
{
    delete ui;
}

void Clientinterface::on_registerButton_clicked()
{
    registeinterface *w=new registeinterface(this);
    this->hide();
    connect(w,&registeinterface::reshowsignal,this,&Clientinterface::on_clicked_reshow);
    w->show();

}

void Clientinterface::on_clicked_reshow()
{
    this->show();
}

void Clientinterface::on_okButton_clicked()
{
    dataBase d;
    d.createConnection();
    d.queryAll();
    QString account=(ui->accountLine)->text();
    QString password=(ui->passwordLine)->text();
    bool flag=d.selectByaccount(account,password);
    if(flag){
        QMessageBox::warning(this,tr("Notice"),tr("Success Log in!"),QMessageBox::Yes);
        ClientDialog *client=new ClientDialog();
        this->close();
        client->show();


    }else{
        QMessageBox::warning(this,tr("Warning"),tr(" account or password error"),QMessageBox::Yes);
    }
}
