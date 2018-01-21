#include "database.h"
#include <QString>
dataBase::dataBase()
{

}
bool dataBase::createConnection()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    qDebug() << "无法建立数据库连接";
    db.setDatabaseName(".//qtDb.db");
    if( !db.open())
    {
        qDebug() << "无法建立数据库连接";
        return false;
    }
    return true;
}

//创建数据库表
bool dataBase::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table usermessage(account varchar primary key,password varchar)");
    if(success)
    {
        qDebug() << QObject::tr("数据库表创建成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("数据库表创建失败！\n");
        return false;
    }
}

//向数据库中插入记录
bool dataBase::insert(QString account,QString password)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("insert into usermessage values(?, ?)");
        query.bindValue(0, account);
        query.bindValue(1, password);
        bool success=query.exec();
        if(!success)
        {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
            return false;
        }

    return true;
}

//查询所有信息
void dataBase::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from usermessage");
    QSqlRecord rec = query.record();


    while(query.next())
    {
        for(int index = 0; index < 2; index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
}


bool dataBase::selectByaccount(QString account,QString password)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("select * from usermessage where account=?");
    query.addBindValue(account);
    query.exec();
    if( query.next()){
        qDebug()<<query.value(1).toString();
        if(password==query.value(1).toString()){

            return true;
        }
         else{
            return false;
        }
    }
     else{
        return false;
    }
}




