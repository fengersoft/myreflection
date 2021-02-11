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
    else
    {
        return 0;
    }


}

void SetSubjectDialog::setSubJectInfo(SubJectInfo& subjectInfo)
{
    ui->edtSubject->setText(subjectInfo.subject);
    ui->edtRemark->setText(subjectInfo.remark);
    int m = subjectInfo.cate;
    for (int i = 0; i < ui->cbbCate->count(); i++)
    {
        if (ui->cbbCate->itemData(i).toInt() == m)
        {
            ui->cbbCate->setCurrentIndex(i);
            break;
        }
    }

}

void SetSubjectDialog::setSubjectTypeHide()
{
    ui->lblSubjectType->setHidden(true);
    ui->grpSubjectType->setHidden(true);

}

void SetSubjectDialog::on_btnCancel_clicked()
{
    reject();
}

void SetSubjectDialog::on_btnOk_clicked()
{
    accept();
}
