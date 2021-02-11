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
    qDebug() << "~SubjectWidget()";
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

QString SubjectWidget::subject()
{
    m_subject = ui->lblSubject->text();
    return m_subject;
}

void SubjectWidget::setSubject(const QString& subject)
{
    m_subject = subject;
    ui->lblSubject->setText(m_subject);
}

QString SubjectWidget::remark()
{
    m_remark = ui->lblRemark->text();
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

int SubjectWidget::subjectType()
{

    return m_subjectType;
}

void SubjectWidget::setSubjectType(int subjectType)
{
    m_subjectType = subjectType;
    ui->btnCard->setHidden(m_subjectType != SubjectType::stCard);
    ui->btnAnswer->setHidden(m_subjectType != SubjectType::stInfo);
}

void SubjectWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(QColor(197, 197, 197));
    painter.drawLine(0, height(), width(), height());
    painter.end();

}

void SubjectWidget::on_btnCard_clicked()
{
    QString sql = QString("insert into report(pid,card,subjectType) values (%1,1,%2)").arg(m_id).arg(m_subjectType);
    sqliteDao()->sqliteWrapper()->execute(sql);
}

void SubjectWidget::on_btnAnswer_clicked()
{
    QString s;
    bool ret = setValue("输入想法", "想法", s);
    if (ret == true)
    {
        QString sql = QString("insert into report(pid,info,subjectType) values (%1,'%2',%3)").arg(m_id).arg(s).arg(m_subjectType);
        sqliteDao()->sqliteWrapper()->execute(sql);

    }

}

void SubjectWidget::on_btnInfos_clicked()
{
    emit onGetSubInfos(m_id);
}

int SubjectWidget::InfoNum() const
{
    return m_InfoNum;
}

void SubjectWidget::setInfoNum(int InfoNum)
{
    m_InfoNum = InfoNum;
    ui->lblNum->setText(QString("%1").arg(InfoNum));
}

int SubjectWidget::cate() const
{
    return m_cate;
}

void SubjectWidget::setCate(int cate)
{
    m_cate = cate;
}
