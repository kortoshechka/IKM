#include "postwidget.h"

PostWidget::PostWidget(Database *db, QWidget *parent)
    : QWidget(parent), db(db)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    postTable = new QTableWidget(this);
    postTable->setColumnCount(4);
    postTable->setHorizontalHeaderLabels({"ID", "User", "Title", "Content"});
    layout->addWidget(postTable);

    userComboBox = new QComboBox(this);
    layout->addWidget(userComboBox);

    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Title");
    layout->addWidget(titleEdit);

    contentEdit = new QLineEdit(this);
    contentEdit->setPlaceholderText("Content");
    layout->addWidget(contentEdit);

    addButton = new QPushButton("Добавить пост", this);
    connect(addButton, &QPushButton::clicked, this, &PostWidget::addPost);
    layout->addWidget(addButton);

    deleteButton = new QPushButton("Удалить пост", this);
    connect(deleteButton, &QPushButton::clicked, this, &PostWidget::deletePost);
    layout->addWidget(deleteButton);

    // Загрузка пользователей в ComboBox
    QSqlQuery query = db->executeQuery("SELECT user_id, username FROM Users");
    while (query.next()) {
        userComboBox->addItem(query.value(1).toString(), query.value(0).toInt());
    }

    loadPosts();
}

void PostWidget::loadPosts() {
    postTable->setRowCount(0);
    QSqlQuery query = db->executeQuery("SELECT p.post_id, u.username, p.title, p.content FROM Posts p JOIN Users u ON p.user_id = u.user_id");

    while (query.next()) {
        int row = postTable->rowCount();
        postTable->insertRow(row);
        postTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        postTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        postTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        postTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
    }
}

void PostWidget::addPost() {
    int userId = userComboBox->currentData().toInt();
    QString title = titleEdit->text();
    QString content = contentEdit->text();

    if (title.isEmpty() || content.isEmpty()) {
        QMessageBox::warning(this, "Осторожно", "Title и content не может быть пустым!");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Posts (user_id, title, content) VALUES (:user_id, :title, :content)");
    query.bindValue(":user_id", userId);
    query.bindValue(":title", title);
    query.bindValue(":content", content);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to add post: " + query.lastError().text());
    } else {
        loadPosts();
        titleEdit->clear();
        contentEdit->clear();
    }
}

void PostWidget::deletePost() {
    int row = postTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Осторожно", "Выберете пост для удаления!");
        return;
    }

    int id = postTable->item(row, 0)->text().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM Posts WHERE post_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete post: " + query.lastError().text());
    } else {
        loadPosts();
    }
}
