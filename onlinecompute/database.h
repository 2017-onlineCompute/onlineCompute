#ifndef DATABASE_H
#define DATABASE_H
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>

class dataBase
{
public:
    dataBase();
      bool createConnection();  //创建一个连接
      bool createTable();       //创建数据库表
      bool insert(QString account,QString password);     //出入数据
      void queryAll();          //查询所有信息
      bool updateById(int id);  //更新
      bool selectByaccount(QString account,QString password);  //删除
      bool sortById();          //排
};

#endif // DATABASE_H
