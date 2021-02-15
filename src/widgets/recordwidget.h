#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include "../api/sql/sqlitedao.h"
#include <QPainter>
#include <QDateTime>
#include "subjectwidget.h"

namespace Ui
{
class RecordWidget;
}

class RecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecordWidget(QWidget* parent = nullptr);
    ~RecordWidget();

    QString subject() const;
    void setSubject(const QString& subject);

    QDateTime createTime() const;
    void setCreateTime(const QDateTime& createTime);

    QString info() const;
    void setInfo(const QString& info);
    SubjectType subjectType() const;
    void setSubjectType(SubjectType subjectType);

    int id() const;
    void setId(int id);
    int pid() const;
    void setPid(int pid);

signals:
    void editInfo(RecordWidget* w);
    void addInfo(RecordWidget* w);
protected:
    void paintEvent(QPaintEvent* event);
private slots:
    void on_btnEdit_clicked();

    void on_btnAdd_clicked();

private:
    Ui::RecordWidget* ui;
    QString m_subject;
    QDateTime m_createTime;
    QString m_info;
    SubjectType m_subjectType;
    int m_id;
    int m_pid;
};

#endif // RECORDWIDGET_H
