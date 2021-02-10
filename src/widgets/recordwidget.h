#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include "../api/sql/sqlitedao.h"
#include <QPainter>
#include <QDateTime>

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
protected:
    void paintEvent(QPaintEvent* event);
private:
    Ui::RecordWidget* ui;
    QString m_subject;
    QDateTime m_createTime;
    QString m_info;
};

#endif // RECORDWIDGET_H
