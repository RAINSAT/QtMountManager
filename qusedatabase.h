#ifndef QUSEDATABASE_H
#define QUSEDATABASE_H
#include <QSqlQuery>
#include <qobject.h>


class QAbstractDataManager;

class QUseDatabase :public QObject
{
	Q_OBJECT
public:
	QUseDatabase(int index);
    ~QUseDatabase();

public:
    bool InsertDatabase(QString,QString);
	bool DelDataFronDatabase(int);
    QStringList ExecQuerySelectAll();

private:
   bool CreateDatabase();
   int GetMaxIdFromDatabase();

private:
	QAbstractDataManager* manager;
};

#endif // QUSEDATABASE_H
