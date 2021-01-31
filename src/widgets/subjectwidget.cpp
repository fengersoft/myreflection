#include "subjectwidget.h"
#include "ui_subjectwidget.h"

SubjectWidget::SubjectWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SubjectWidget)
{
    ui->setupUi(this);
}

SubjectWidget::~SubjectWidget()
{
    delete ui;
}

QString SubjectWidget::cateName() const
{
    return m_cateName;
}

void SubjectWidget::setCateName(const QString& cateName)
{
    m_cateName = cateName;
    ui->lblCate->setText(m_cateName);
}

QString SubjectWidget::subject() const
{
    return m_subject;
}

void SubjectWidget::setSubject(const QString& subject)
{
    m_subject = subject;
    ui->lblSubject->setText(m_subject);
}

QString SubjectWidget::remark() const
{
    return m_remark;
}

void SubjectWidget::setRemark(const QString& remark)
{
    m_remark = remark;
    ui->lblRemark->setText(m_remark);
}

int SubjectWidget::id()
{
    return m_id;
}

void SubjectWidget::setId(int id)
{
    m_id = id;
}

int SubjectWidget::subjectType() const
{
    return m_subjectType;
}

void SubjectWidget::setSubjectType(int subjectType)
{
    m_subjectType = subjectType;
    ui->btnCard->setHidden(m_subjectType != 2);
}

void SubjectWidget::on_btnCard_clicked()
{
    QString sql = QString("insert into report(pid,card,subjectType) values (%1,1,%2)").arg(m_id).arg(m_subjectType);
    sqliteDao()->sqliteWrapper()->execute(sql);
}
