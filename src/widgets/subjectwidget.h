#ifndef SUBJECTWIDGET_H
#define SUBJECTWIDGET_H

#include <QWidget>

namespace Ui {
class SubjectWidget;
}

class SubjectWidget : public QWidget
{
  Q_OBJECT

public:
  explicit SubjectWidget(QWidget *parent = nullptr);
  ~SubjectWidget();

private:
  Ui::SubjectWidget *ui;
};

#endif // SUBJECTWIDGET_H
