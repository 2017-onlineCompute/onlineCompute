#include "clientinterface.h"
#include "ui_clientinterface.h"
#include "registeinterface.h"
#include "ui_clientinterface.h"
#include <iostream>
#include "database.h"
#include <QMessageBox>
Clientinterface::Clientinterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clientinterface)
{

    ui->setupUi(this);
     ui->passwordLine->setEchoMode(QLineEdit::Password);
}

Clientinterface::~Clientinterface()
{
    delete ui;
}

void Clientinterface::on_registerButton_clicked()
{
    registeinterface *w=new registeinterface(this);
    this->hide();
   connect(w,SIGNAL(reshowsignal()),this,SLOT(on_clicked_reshow()));
    //connect(w,&registeinterface::reshowsignal,this,&Clientinterface::on_clicked_reshow);
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
   QString account=ui->accountLine->text();
   QString passowrd=ui->passwordLine->text();
   bool flag=d.selectByaccount(account,passowrd);
   if(flag){
       qDebug("yes");

   }else{
       QMessageBox::warning(this,tr("Warning"),tr(" account or password error"),QMessageBox::Yes);
   }
}
