#pragma once
#include "QAbstractDataManager.h"
#include <qsqldatabase.h>
#include "QSetini.h"

class QSQLiteDataBase final: public QAbstractDataManager
{
public:
	explicit QSQLiteDataBase(QString dbName,QString dbHost,QString dbUserName,QString dbPassword, int dbPort = 0);
	~QSQLiteDataBase();
public:
	virtual bool OpenDatabase() override;
	virtual bool ExecQuery(QString list) override;
	virtual QStringList ExeQuerySelect(QString query) override;

private:
	QSqlDatabase db;

#ifdef Q_SETFILE
	QSetini* ini;
#endif
};

