#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include "./api/dialogs/setvaluedialog.h"
#include "./api/sql/sqlitedao.h"
#include <QStandardItemModel>
#include <QListWidget>
#include "./dialogs/setsubjectdialog.h"
#include "./widgets/subjectwidget.h"
#include "./widgets/recordwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    ///显示类别
    void showCates();
    ///显示主题
    void showSubjects(QString whereStr);
    void showRecords(QString whereStr);
    void onGetSubInfos(int id);

private slots:
    void on_btnAdd_clicked();
    void onbtnAddTriggered(bool checked = false);


    void on_btnCate_clicked();

    void on_btnSubject_clicked();

    void on_btnRecord_clicked();

    void on_lvCate_itemClicked(QListWidgetItem* item);

    void on_btnSet_clicked();

private:
    Ui::MainWindow* ui;

};
#endif // MAINWINDOW_H
