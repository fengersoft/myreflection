#ifndef SETSUBJECTDIALOG_H
#define SETSUBJECTDIALOG_H

#include <QDialog>
#include "src/api/sql/sqlitedao.h"

namespace Ui
{
class SetSubjectDialog;
}
struct SubJectInfo
{
    QString subject;
    QString remark;
    int cate;
    int subjectType;
};

class SetSubjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetSubjectDialog(QWidget* parent = nullptr);
    ~SetSubjectDialog();
    void getSubjectInfo(SubJectInfo& subjectInfo);
    int getSubjectType();
    void setSubJectInfo(SubJectInfo& subjectInfo);
    void setSubjectTypeHide();
private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::SetSubjectDialog* ui;
};

#endif // SETSUBJECTDIALOG_H
