#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showCates();
    showSubjects("where 2>1");
    showRecords("where 2>1");






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCates()
{
    ui->wgtPages->setCurrentWidget(ui->pageCate);
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

void MainWindow::showSubjects(QString whereStr)
{
    ui->wgtPages->setCurrentWidget(ui->pageSubject);
    QSqlQuery qry;
    QString sql = "select a.*,b.name as cateName from subject a left join cate b on a.pid=b.id " + whereStr + " order by a.id";
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    ui->lvSubject->clear();
    while (qry.next())
    {
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(ui->lvSubject->width() - 24, 100));
        SubjectWidget* w = new SubjectWidget(this);
        w->setCateName(qry.value("catename").toString());
        w->setSubject(qry.value("name").toString());
        w->setRemark(qry.value("remark").toString());
        w->setId(qry.value("id").toInt());
        w->setSubjectType(qry.value("subjectType").toInt());
        connect(w, &SubjectWidget::onGetSubInfos, this, &MainWindow::onGetSubInfos);
        ui->lvSubject->addItem(item);
        ui->lvSubject->setItemWidget(item, w);


    }
}

void MainWindow::showRecords(QString whereStr)
{
    ui->wgtPages->setCurrentWidget(ui->pageRecord);
    QString sql = "select b.name subjectName,a.subjectType,a.card,"
                  "a.value,a.info,a.createtime  from report a left join subject"
                  " b on a.pid=b.id " + whereStr + " order by a.createTime desc";
    QSqlQuery qry;
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    ui->lvRecord->clear();
    while (qry.next())
    {
        int subjectType = qry.value("subjectType").toInt();
        QListWidgetItem* item = new QListWidgetItem();
        if (subjectType == SubjectType::stCard)
        {
            item->setSizeHint(QSize(ui->lvRecord->width() - 24, 120));
        }
        else
        {
            item->setSizeHint(QSize(ui->lvRecord->width(), 160));
        }

        ui->lvRecord->addItem(item);
        RecordWidget* w = new RecordWidget(this);
        w->setSubject(qry.value("subjectName").toString());
        w->setCreateTime(qry.value("createtime").toDateTime());

        if (subjectType == SubjectType::stCard)
        {
            w->setInfo("已打卡");
        }
        else if (subjectType == SubjectType::stInfo)
        {
            w->setInfo(qry.value("info").toString());
        }
        ui->lvRecord->setItemWidget(item, w);


    }

}

void MainWindow::onGetSubInfos(int id)
{
    QString whereStr = QString("where a.pid=%1").arg(id);
    showRecords(whereStr);

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
            qDebug() << sql;
            sqliteDao()->sqliteWrapper()->execute(sql);

        }
        delete dlg;
    }

}



void MainWindow::on_btnCate_clicked()
{
    showCates();
}

void MainWindow::on_btnSubject_clicked()
{
    showSubjects("where 2>1");
}

void MainWindow::on_btnRecord_clicked()
{
    ui->wgtPages->setCurrentWidget(ui->pageRecord);

}

void MainWindow::on_lvCate_itemClicked(QListWidgetItem* item)
{
    if (item == nullptr)
    {
        return;
    }

    int id = item->data(Qt::UserRole).toInt();
    QString whereStr = QString("where a.pid=%1").arg(id);
    showSubjects(whereStr);
}

void MainWindow::on_btnSet_clicked()
{
    ui->wgtPages->setCurrentWidget(ui->pageSet);

}
