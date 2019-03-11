
#include <qsqlquery.h>
#include <qobject.h>
#include <qvariant.h>
#include "QSQLiteDataBase.h"
#include "QSetini.h"

QSQLiteDataBase::QSQLiteDataBase(QString dbName, QString dbHost, QString dbUserName, QString dbPassword, int dbPort)
{
	this->_dbName = dbName;
	this->_dbHost = dbHost;
	this->_dbUserName = dbUserName;
	this->_dbPassword = dbPassword;
	this->_dbPort = dbPort;

	/*this->ini = new QSetini(QString::fromLocal8Bit("./mpz.ini"));
	this->ini->WriteIni();*/
}


QSQLiteDataBase::~QSQLiteDataBase()
{
	//析构时关闭连接
	this->db.close();
}

bool QSQLiteDataBase::OpenDatabase()
{
	this->db = QSqlDatabase::addDatabase("QSQLITE");
	this->db.setDatabaseName(_dbName);
	this->db.setHostName(_dbHost);
	this->db.setPassword(_dbPassword);
	this->db.setUserName(_dbUserName);
	if (db.open())
	{
		return true;
	}

	return false;
}

bool QSQLiteDataBase::ExecQuery(QString list)
{
	QSqlQuery query(db);
	return query.exec(list);
}

QStringList QSQLiteDataBase::ExeQuerySelect(QString query)
{
	QSqlQuery querys(db);
	querys.exec(query);
	QStringList strList;
	while (querys.next())
	{
		QString id = querys.value(QString::fromLocal8Bit("id")).toString();
		QString mount = querys.value(QString::fromLocal8Bit("mount")).toString();
		QString password = querys.value(QString::fromLocal8Bit("password")).toString();
		strList << id << mount << password;
	}
	return strList;
}
