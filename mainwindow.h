#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "userwidget.h"
#include "postwidget.h"
#include "commentwidget.h"
#include "database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTabWidget *tabWidget;
    UserWidget *userWidget;
    PostWidget *postWidget;
    CommentWidget *commentWidget;
    Database db;
};

#endif // MAINWINDOW_H
