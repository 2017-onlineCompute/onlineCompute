#include "registeinterface.h"
#include "ui_registeinterface.h"
#include "database.h"
#include <QMessageBox>
registeinterface::registeinterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registeinterface)
{
    ui->setupUi(this);
    (ui->passwordLine)->setEchoMode(QLineEdit::Password);
}

registeinterface::~registeinterface()
{
    delete ui;
}

void registeinterface::on_okButton_clicked()
{
    emit reshowsignal();
    QString account=(ui->phoneLine)->text();
    QString passowrd=(ui->passwordLine)->text();
    dataBase d;
    d.createConnection();
    d.createTable();
    if(account!=""&& passowrd!=""){

    if( d.insert(account,passowrd)){
      QMessageBox::warning(this,tr("Notice"),tr("Success register!"),QMessageBox::Yes);
    }
    } else{
       QMessageBox::warning(this,tr("Warning"),tr("Please enter the account or password"),QMessageBox::Yes);
    }
    d.queryAll();
    this->close();
}

void registeinterface::on_exitButton_clicked()
{
    emit reshowsignal();
    this->close();
}



