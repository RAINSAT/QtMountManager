#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qusedatabase.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonshow_clicked();

    void on_pushButtonDel_clicked();

	void on_comboBox_changed(int index);

signals:
    void finishDel();
    void finishAdd();


private:
    Ui::Widget *ui;
    QUseDatabase *db;
};

#endif // WIDGET_H
