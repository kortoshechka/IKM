#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Подключение к базе данных
    if (!db.connect()) {
        QMessageBox::critical(this, "Error", "Failed to connect to database!");
    }

    // Создание вкладок
    tabWidget = new QTabWidget(this);
    userWidget = new UserWidget(&db, tabWidget);
    postWidget = new PostWidget(&db, tabWidget);
    commentWidget = new CommentWidget(&db, tabWidget);

    tabWidget->addTab(userWidget, "Users");
    tabWidget->addTab(postWidget, "Posts");
    tabWidget->addTab(commentWidget, "Comments");

    setCentralWidget(tabWidget);
    setWindowTitle("Database Manager");
    resize(800, 600);
}

MainWindow::~MainWindow() {}
