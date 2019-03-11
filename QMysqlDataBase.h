#pragma once
#include "QAbstractDataManager.h"
#include "qsqldatabase.h"

class QMysqlDataBase final : public QAbstractDataManager
{
	Q_OBJECT
public:
	QMysqlDataBase();
	QMysqlDataBase(QString dbName, QString dbHost, QString dbUserName, QString dbPassword,int dbPort);
	~QMysqlDataBase();
public:
	bool OpenDatabase() override;
	bool ExecQuery(QString list) override;
	QStringList ExeQuerySelect(QString query) override;
private:
	QSqlDatabase db;
};

