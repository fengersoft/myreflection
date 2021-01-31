#include "setsubjectdialog.h"
#include "ui_setsubjectdialog.h"

SetSubjectDialog::SetSubjectDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetSubjectDialog)
{
    ui->setupUi(this);
    QSqlQuery qry;
    QString sql = "select * from cate order by id";
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    while (qry.next())
    {
        ui->cbbCate->addItem(qry.value("name").toString(), qry.value("id").toInt());

    }

}

SetSubjectDialog::~SetSubjectDialog()
{
    delete ui;
}

void SetSubjectDialog::getSubjectInfo(SubJectInfo& subjectInfo)
{
    subjectInfo.subject = ui->edtSubject->text();
    subjectInfo.remark = ui->edtRemark->text();
    subjectInfo.cate = ui->cbbCate->currentData(Qt::UserRole).toInt();
    subjectInfo.subjectType = getSubjectType();

}

int SetSubjectDialog::getSubjectType()
{
    if (ui->rdSbType1->isChecked())
    {
        return 1;
    }
    else if (ui->rdSbType2->isChecked())
    {
        return 2;
    }
    else if (ui->rdSbType3->isChecked())
    {
        return 3;
    }

}

void SetSubjectDialog::on_btnCancel_clicked()
{
    reject();
}

void SetSubjectDialog::on_btnOk_clicked()
{
    accept();
}
