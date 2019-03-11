#include "QSetini.h"
#include <qsettings.h>


QSetini::QSetini(QString fileName)
{
	this->fName = fileName;
	this->setting = new QSettings(fileName,QSettings::IniFormat);
	this->setting->setUserIniPath("./");
}


QSetini::~QSetini()
{
	this->setting->deleteLater();
}

void QSetini::WriteIni()
{
	this->setting->beginGroup("SQLITE");
	this->setting->setValue("HasCreatedDB", 0);
	this->setting->endGroup();
}

QStringList QSetini::ReadIni()
{
	return QStringList();
}

bool QSetini::ChangeIni()
{
	return false;
}

