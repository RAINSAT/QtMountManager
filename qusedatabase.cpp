#include "qusedatabase.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlRecord>
#include <QStringList>

#include "QSQLiteDataBase.h"
#include "QMysqlDataBase.h"

QUseDatabase::QUseDatabase(int index)
{
	switch (index)
	{
	case 0:
		this->manager = new QSQLiteDataBase("account.db","localhost","root","123456");//使用有参构造函数
		this->manager->OpenDatabase();
		break;
	case 1:
		this->manager = new QMysqlDataBase("MountManager","47.104.255.248","root","123456",3306);
		this->manager->OpenDatabase();
		break;
	}
}
QUseDatabase::~QUseDatabase()
{
	delete this->manager;
	manager = nullptr;
}


bool QUseDatabase::CreateDatabase()
{
    //创建数据库表
   QSqlQuery query;
   QString sqlquery="create table count(id int primary key,account varchar,password varchar)";
   bool isSuccess= query.exec(sqlquery);
   if(isSuccess)
   {
       qDebug()<<"create success";
   }
   return true;

}

//获取最大id
int QUseDatabase::GetMaxIdFromDatabase()
{
    int val=0;
    QSqlQuery exeque("select max(id) from count ");
    while(exeque.next())
    {
        val=exeque.value(0).toInt();
    }
    return val;
}

//执行插入数据
bool QUseDatabase::InsertDatabase(QString acc,QString password)
{
	QString query = QString("insert into mount(mount,password) VALUES ('%1','%2');").arg(acc).arg(password);
	return this->manager->ExecQuery(query);
}

//执行查询操作
QStringList QUseDatabase::ExecQuerySelectAll()
{
    QString select = "select * from mount";
	return this->manager->ExeQuerySelect(select);
}

//执行删除操作
bool QUseDatabase::DelDataFronDatabase(int id)
{
    QString delstr=QString("delete from mount where id=%1").arg(id);
    QSqlQuery delquery;
    bool isok=delquery.exec(delstr);
    if(isok)
    {
        qDebug()<<"delete success";
		return true;
    }
	return false;
}
