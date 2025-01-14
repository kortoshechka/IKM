#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include "database.h"

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(Database *db, QWidget *parent = nullptr);

private slots:
    void loadUsers();
    void addUser();
    void deleteUser();

private:
    QTableWidget *userTable;
    QLineEdit *usernameEdit;
    QLineEdit *emailEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    Database *db;
};

#endif // USERWIDGET_H
