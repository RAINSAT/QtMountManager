#pragma once
#include <qobject.h>

class QSettings;

class QSetini : public QObject
{
	Q_OBJECT
public:
	explicit QSetini(QString fileName);
	~QSetini();
public:
	void WriteIni();
	QStringList ReadIni();
	bool ChangeIni();
private:
	QSettings* setting;
	QString fName;
};

