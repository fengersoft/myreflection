#include "recordwidget.h"
#include "ui_recordwidget.h"

RecordWidget::RecordWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::RecordWidget)
{
    ui->setupUi(this);
}

RecordWidget::~RecordWidget()
{
    delete ui;
}

QString RecordWidget::subject() const
{
    return m_subject;
}

void RecordWidget::setSubject(const QString& subject)
{
    m_subject = subject;
    ui->lblSubject->setText(m_subject);

}

QDateTime RecordWidget::createTime() const
{
    return m_createTime;
}

void RecordWidget::setCreateTime(const QDateTime& createTime)
{
    m_createTime = createTime;
    ui->lblDate->setText(m_createTime.toString("yyyy-MM-dd hh:mm:ss"));
}

QString RecordWidget::info() const
{
    return m_info;
}

void RecordWidget::setInfo(const QString& info)
{
    m_info = info;
    ui->edtInfo->setText(m_info);
}

void RecordWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(QColor(197, 197, 197));
    painter.drawLine(0, height(), width(), height());
    painter.end();

}

int RecordWidget::id() const
{
    return m_id;
}

void RecordWidget::setId(int id)
{
    m_id = id;
}

SubjectType RecordWidget::subjectType() const
{
    return m_subjectType;
}

void RecordWidget::setSubjectType(SubjectType subjectType)
{
    m_subjectType = subjectType;
    ui->btnEdit->setHidden(m_subjectType != stInfo);
}

void RecordWidget::on_btnEdit_clicked()
{
    emit editInfo(this);
}
