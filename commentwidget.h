#ifndef COMMENTWIDGET_H
#define COMMENTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include "database.h"

class CommentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentWidget(Database *db, QWidget *parent = nullptr); // Объявление конструктора

private slots:
    void loadComments();
    void addComment();
    void deleteComment();

private:
    QTableWidget *commentTable;
    QComboBox *postComboBox;
    QComboBox *userComboBox;
    QLineEdit *contentEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    Database *db;
};

#endif // COMMENTWIDGET_H
