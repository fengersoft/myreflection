#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showCates();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCates()
{
    QSqlQuery qry;
    QString sql = "select name,id from cate order by id";
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    ui->lvCate->clear();
    while (qry.next())
    {
        QListWidgetItem* item = new QListWidgetItem(ui->lvCate);
        item->setSizeHint(QSize(500, 48));
        QFont font = item->font();
        font.setPointSize(11);
        item->setFont(font);
        item->setText(qry.value("name").toString());
        item->setData(Qt::UserRole, qry.value("id").toInt());
        ui->lvCate->addItem(item);

    }

}


void MainWindow::on_btnAdd_clicked()
{
    QStringList stlAdd;
    QMenu* menu = new QMenu(this);
    stlAdd << "添加类别";
    stlAdd << "添加主题";
    for (int i = 0; i < stlAdd.count(); i++)
    {
        QAction* act = new QAction(this);
        act->setText(stlAdd[i]);
        menu->addAction(act);
        connect(act, &QAction::triggered, this, &MainWindow::onbtnAddTriggered);
    }
    QPoint pt = QPoint(0, ui->btnAdd->height());
    pt = ui->btnAdd->mapToGlobal(pt);
    menu->exec(pt);
    delete  menu;
}

void MainWindow::onbtnAddTriggered(bool checked)
{
    Q_UNUSED(checked);
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "添加类别")
    {
        QString value;
        bool ret = setValue("新增类别", "类别", value);
        if (ret == true)
        {
            sqliteDao()->sqliteWrapper()->execute("insert into cate(name) values ('" + value + "')");
            showCates();

        }

    }
    else if (act->text() == "添加主题")
    {
        SetSubjectDialog* dlg = new SetSubjectDialog();
        dlg->setWindowTitle("添加主题");
        int ret = dlg->exec();
        if (ret == QDialog::Accepted)
        {
            SubJectInfo subjectInfo;
            dlg->getSubjectInfo(subjectInfo);
            QString sql = QString("insert into subject(pid,name,remark,subjectType)"
                                  " values (%1,'%2','%3',%4)")
                          .arg(subjectInfo.cate)
                          .arg(subjectInfo.subject).arg(subjectInfo.remark).arg(subjectInfo.subjectType);
            sqliteDao()->sqliteWrapper()->execute(sql);

        }
        delete dlg;
    }

}



void MainWindow::on_btnCate_clicked()
{
    ui->wgtPages->setCurrentWidget(ui->pageCate);
}

void MainWindow::on_btnSubject_clicked()
{
    ui->wgtPages->setCurrentWidget(ui->pageSubject);
}
