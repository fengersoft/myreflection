#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    QStringList stlAdd;
    QMenu* menu = new QMenu(this);
    stlAdd << "添加类别";
    for (int i = 0; i < stlAdd.count(); i++)
    {
        QAction* act = new QAction(this);
        act->setText(stlAdd[i]);
        menu->addAction(act);
        connect(act, &QAction::triggered, this, &MainWindow::onbtnAddTriggered);
    }
    QPoint pt = QPoint(0, ui->btnAdd->height());
    pt = ui->btnAdd->mapToGlobal(pt);
    menu->exec(pt);
    delete  menu;
}

void MainWindow::onbtnAddTriggered(bool checked)
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "添加类别")
    {

    }

}
