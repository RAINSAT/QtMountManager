#include "QMysqlDataBase.h"
#include <qmessagebox.h>
#include <qdebug.h>
#include <qsqlquery.h>

QMysqlDataBase::QMysqlDataBase()
{
}

QMysqlDataBase::QMysqlDataBase(QString dbName, QString dbHost, QString dbUserName, QString dbPassword,int dbPort)
{
	this->_dbName = dbName;
	this->_dbHost = dbHost;
	this->_dbUserName = dbUserName;
	this->_dbPassword = dbPassword;
	this->_dbPort = dbPort;
}


QMysqlDataBase::~QMysqlDataBase()
{
	//析构时关闭连接
	this->db.close();
}

bool QMysqlDataBase::OpenDatabase()
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setDatabaseName(this->_dbName);
	db.setHostName(this->_dbHost);
	db.setUserName(this->_dbUserName);
	db.setPassword(this->_dbPassword);
	if (!db.open())
	{
		qDebug() << "connect failed";
		return false;
	}
	return true;
}

bool QMysqlDataBase::ExecQuery(QString list)
{
	QSqlQuery query(db);
	return query.exec(list);
}

QStringList QMysqlDataBase::ExeQuerySelect(QString query)
{
	QSqlQuery querys(db);
	querys.exec(query);
	QStringList strList;
	while (querys.next())
	{
		QString id = querys.value("id").toString();
		QString mount = querys.value("mount").toString();
		QString password = querys.value("password").toString();
		strList << id << mount << password;
	}
	return strList;
}

