#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include "database.h"

class PostWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PostWidget(Database *db, QWidget *parent = nullptr);

private slots:
    void loadPosts();
    void addPost();
    void deletePost();

private:
    QTableWidget *postTable;
    QComboBox *userComboBox;
    QLineEdit *titleEdit;
    QLineEdit *contentEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    Database *db;
};

#endif // POSTWIDGET_H
