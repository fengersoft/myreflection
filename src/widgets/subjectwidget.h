#ifndef SUBJECTWIDGET_H
#define SUBJECTWIDGET_H

#include <QWidget>
#include "../api/sql/sqlitedao.h"
#include <QPainter>
#include "../api/dialogs/setvaluedialog.h"
namespace Ui
{
class SubjectWidget;
}

///打卡类型
enum SubjectType
{
    stCard = 2,
    stInfo = 1
};

class SubjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectWidget(QWidget* parent = nullptr);
    ~SubjectWidget();

    QString cateName() const;
    void setCateName(const QString& cateName);

    QString subject() const;
    void setSubject(const QString& subject);

    QString remark() const;
    void setRemark(const QString& remark);

    int id();
    void setId(int id);

    int subjectType() const;
    void setSubjectType(int subjectType);
signals:
    void onGetSubInfos(int id);
protected:
    void paintEvent(QPaintEvent* event);
private slots:
    void on_btnCard_clicked();

    void on_btnAnswer_clicked();

    void on_btnInfos_clicked();

private:
    Ui::SubjectWidget* ui;
    QString m_cateName;
    QString m_subject;
    QString m_remark;
    int m_id;
    int m_subjectType;
};

#endif // SUBJECTWIDGET_H
