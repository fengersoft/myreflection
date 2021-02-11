#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addContextMenus();
    m_reportOrder = false;

    showSubjects("where 2>1");






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
    QString sql = "select a.*,b.name as cateName,c.num from subject a left join cate b on a.pid=b.id left join (select pid as sid,count(*) as num from report group by pid) c on a.id=c.sid " + whereStr + " order by a.id";
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
        w->setCate(qry.value("pid").toInt());
        w->setInfoNum(qry.value("num").toInt());
        connect(w, &SubjectWidget::onGetSubInfos, this, &MainWindow::onGetSubInfos);
        ui->lvSubject->addItem(item);
        ui->lvSubject->setItemWidget(item, w);


    }
}



void MainWindow::showRecords(QString whereStr)
{
    if (whereStr == "")
    {
        whereStr = m_recordStr;
    }
    else
    {
        m_recordStr = whereStr;
    }
    QString orderStr = m_reportOrder == true ? "asc" : "desc";

    ui->wgtPages->setCurrentWidget(ui->pageRecord);
    QString sql = "select b.name subjectName,a.subjectType,a.card,"
                  "a.value,a.info,a.createtime  from report a left join subject"
                  " b on a.pid=b.id " + whereStr + " order by a.createTime " + orderStr;
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

void MainWindow::addContextMenus()
{
    QStringList menus;
    menus << "添加" << "修改" << "删除";
    for (int i = 0; i < menus.count(); i++)
    {
        QAction* act = new QAction(this);
        act->setText(menus[i]);
        connect(act, &QAction::triggered, this, &MainWindow::onLvCateActionTriggerd);
        ui->lvCate->addAction(act);
    }

    for (int i = 0; i < menus.count(); i++)
    {
        QAction* act = new QAction(this);
        act->setText(menus[i]);
        connect(act, &QAction::triggered, this, &MainWindow::onLvSubjectActionTriggerd);
        ui->lvSubject->addAction(act);
    }

}

void MainWindow::addCate()
{
    QString value;
    bool ret = setValue("新增类别", "类别", value);
    if (ret == true)
    {
        sqliteDao()->sqliteWrapper()->execute("insert into cate(name) values ('" + value + "')");
        showCates();

    }

}

void MainWindow::editCate()
{
    QListWidgetItem* item = ui->lvCate->currentItem();
    if (item == nullptr)
    {
        return;
    }
    QString value = item->text();
    bool ret = setValue("修改类别", "类别", value);
    if (ret == true)
    {
        sqliteDao()->sqliteWrapper()->execute(QString("update cate set name='%1' where id=%2").arg(value).arg(item->data(Qt::UserRole).toInt()));
        item->setText(value);

    }



}

void MainWindow::deleteCate()
{
    QListWidgetItem* item = ui->lvCate->currentItem();
    if (item == nullptr)
    {
        return;
    }
    int ret = QMessageBox::question(this, "提示", "确定删除选中项吗?");
    if (ret == QMessageBox::No)
    {
        return;
    }
    int id = item->data(Qt::UserRole).toInt();
    QString sql = QString("delete from cate where id=%1").arg(id);
    sqliteDao()->sqliteWrapper()->execute(sql);
    sql = "delete from subject where pid not in (select id from cate)";
    sqliteDao()->sqliteWrapper()->execute(sql);
    sql = "delete from report where pid not in (select id from subject)";
    sqliteDao()->sqliteWrapper()->execute(sql);

    item = ui->lvCate->takeItem(ui->lvCate->currentRow());
    delete item;

}

void MainWindow::addSubject()
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

void MainWindow::editSubject()
{
    QListWidgetItem* item = ui->lvSubject->currentItem();
    if (item == nullptr)
    {
        return;
    }
    SubJectInfo subjectInfo;
    SubjectWidget* w = static_cast<SubjectWidget*>(ui->lvSubject->itemWidget(item));
    SetSubjectDialog* dlg = new SetSubjectDialog();
    dlg->setWindowTitle("修改主题");
    subjectInfo.subject = w->subject();
    subjectInfo.remark = w->remark();
    subjectInfo.cate = w->cate();
    dlg->setSubJectInfo(subjectInfo);
    dlg->setSubjectTypeHide();
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {

        dlg->getSubjectInfo(subjectInfo);
        QString sql = QString("update subject set pid=%1,name='%2',remark='%3' where id=%4")
                      .arg(subjectInfo.cate)
                      .arg(subjectInfo.subject).arg(subjectInfo.remark).arg(w->id());

        sqliteDao()->sqliteWrapper()->execute(sql);

    }
    delete dlg;
}

void MainWindow::deleteSubject()
{
    QListWidgetItem* item = ui->lvSubject->currentItem();
    if (item == nullptr)
    {
        return;
    }
    int ret = QMessageBox::question(this, "提示", "确定删除选中项吗?");
    if (ret == QMessageBox::No)
    {
        return;
    }
    SubjectWidget* w = static_cast<SubjectWidget*>(ui->lvSubject->itemWidget(item));

    int id = w->id();

    QString sql = QString("delete from subject where id=%1").arg(id);
    sqliteDao()->sqliteWrapper()->execute(sql);
    sql = "delete from report where pid not in (select id from subject)";
    sqliteDao()->sqliteWrapper()->execute(sql);

    ui->lvCate->removeItemWidget(item);
    delete item;
    delete w;

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
        addCate();


    }
    else if (act->text() == "添加主题")
    {
        addSubject();

    }

}



void MainWindow::on_btnCate_clicked()
{
    showCates();
}

void MainWindow::on_btnSubject_clicked()
{
    showSubjects("where a.subjectType=1");
}

void MainWindow::on_btnRecord_clicked()
{
    showRecords("where 2>1");


}



void MainWindow::on_btnSet_clicked()
{
    ui->wgtPages->setCurrentWidget(ui->pageSet);

}

void MainWindow::on_btnCard_clicked()
{
    showSubjects("where a.subjectType=2");
}

void MainWindow::on_btnOrder_clicked()
{
    if (ui->wgtPages->currentWidget() == ui->pageRecord)
    {
        m_reportOrder = !m_reportOrder;
        showRecords("");

    }
}

void MainWindow::onLvCateActionTriggerd()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "添加")
    {
        addCate();

    }
    else if (act->text() == "修改")
    {
        editCate();
    }
    else if (act->text() == "删除")
    {
        deleteCate();
    }

}

void MainWindow::onLvSubjectActionTriggerd()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "添加")
    {
        addSubject();

    }
    else if (act->text() == "修改")
    {
        editSubject();
    }
    else if (act->text() == "删除")
    {
        deleteSubject();
    }

}

void MainWindow::on_lvCate_itemDoubleClicked(QListWidgetItem* item)
{
    if (item == nullptr)
    {
        return;
    }

    int id = item->data(Qt::UserRole).toInt();
    QString whereStr = QString("where a.pid=%1").arg(id);
    showSubjects(whereStr);
}

void MainWindow::on_lvSubject_itemDoubleClicked(QListWidgetItem* item)
{
    if (item == nullptr)
    {
        return;
    }
    SubjectWidget* w = static_cast<SubjectWidget*>(ui->lvSubject->itemWidget(item)) ;
    onGetSubInfos(w->id());
}
