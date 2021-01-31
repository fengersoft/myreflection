#include "subjectwidget.h"
#include "ui_subjectwidget.h"

SubjectWidget::SubjectWidget(QWidget *parent) :
                                                QWidget(parent),
                                                ui(new Ui::SubjectWidget)
{
  ui->setupUi(this);
}

SubjectWidget::~SubjectWidget()
{
  delete ui;
}
