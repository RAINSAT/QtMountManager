#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QHeaderView>
#include <qcombobox.h>
#include <qdebug.h>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("AccountManager"));
    setWindowIcon(QIcon(R"(E:\qt\MountManager\icon.png)"));

    QStringList labels;
    labels.append("id");
    labels.append("account");
    labels.append("password");
    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(1);
    ui->tableWidget->insertColumn(2);
    //设置表格行表头
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    //设置表格行标题的对齐方式
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    //将行和列的大小设为与内容相配：
    //ui->tableWidget->resizeColumnsToContents();
     //自动调整最后一列的宽度使它和表格的右边界对齐
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    //隐藏行表头
    ui->tableWidget->verticalHeader()->setVisible(false);
    //禁止编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中一行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

	//设定comboBox
	ui->comboBox->addItem("QSQLITE");
	ui->comboBox->addItem("QMYSQL");
	ui->comboBox->setCurrentIndex(0);

    //信号与槽
    connect(this,SIGNAL(finishDel()),this,SLOT(on_pushButtonshow_clicked()));
    connect(this,SIGNAL(finishAdd()),this,SLOT(on_pushButtonshow_clicked()));

	db = new QUseDatabase(0);
	connect(ui->comboBox, SIGNAL(activated(int)),this,SLOT(on_comboBox_changed(int)));
	
}

Widget::~Widget()
{
    delete ui;
    delete db;
	db=nullptr;
}

void Widget::on_pushButton_clicked()
{
	QString acc = ui->lineEditACC->text();
	QString password = ui->lineEditPASS->text();
	ui->lineEditACC->clear();
	ui->lineEditPASS->clear();
	if (acc.isEmpty() | password.isEmpty())
	{
		QMessageBox::warning(this, "warning", "please input the info", QMessageBox::Ok);
	}
	else
	{
		bool isok = db->InsertDatabase(acc, password);
		if (isok)
		{
			emit finishAdd();
		}
	}
    
}

void Widget::on_pushButtonshow_clicked()
{
	//获得数据库内容
	QStringList strList = this->db->ExecQuerySelectAll();
	int tableRow = strList.size() / 3;
    //设置到QTableList
   ui->tableWidget->setRowCount(tableRow);
   ui->tableWidget->setColumnCount(3);
   //设置单元格内容
   for(int i=0;i<tableRow;i++)
   {
       QTableWidgetItem* itemid =new QTableWidgetItem;
       QTableWidgetItem* itemacc =new QTableWidgetItem;
       QTableWidgetItem* itempass =new QTableWidgetItem;
       itemid->setText(strList[3*i + 0]);
       itemacc->setText(strList[3*i + 1]);
       itempass->setText(strList[3*i + 2]);
       ui->tableWidget->setItem(i,0,itemid);
       ui->tableWidget->setItem(i,1,itemacc);
       ui->tableWidget->setItem(i,2,itempass);
   }

}

void Widget::on_pushButtonDel_clicked()
{
	//获取所选行的id
	QList<QTableWidgetItem*> listItem;
	listItem = ui->tableWidget->selectedItems();
	if (!listItem.isEmpty())
	{
		QVariant item = listItem[0]->data(0);
		bool isok = this->db->DelDataFronDatabase(item.toInt());
		if (isok)
		{
			emit finishDel();
		}
	}

}

void Widget::on_comboBox_changed(int index)
{
	delete this->db;
	db = nullptr;
	qDebug() << "创建新的连接句柄" << index;
	db = new QUseDatabase(index);
}


