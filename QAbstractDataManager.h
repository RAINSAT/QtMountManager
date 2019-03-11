#pragma once
#include "qobject.h"

class QAbstractInterFaceDB : public QObject
{
	Q_OBJECT
public:
	QAbstractInterFaceDB() = default;
	virtual ~QAbstractInterFaceDB() = default;
public:
	virtual bool ExecQuery(QString list) = 0;
	virtual QStringList ExeQuerySelect(QString query) = 0;
	
};

class QAbstractDataManager : public QAbstractInterFaceDB
{
	Q_OBJECT
public:
	QAbstractDataManager();
	virtual ~QAbstractDataManager();
public:
	virtual bool OpenDatabase() = 0;
protected:
	QString _dbName;
	QString _dbHost;
	QString _dbUserName;
	QString _dbPassword;
	int _dbPort;
};

