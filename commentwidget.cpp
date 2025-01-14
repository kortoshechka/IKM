#include "commentwidget.h"

CommentWidget::CommentWidget(Database *db, QWidget *parent)
    : QWidget(parent), db(db)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    commentTable = new QTableWidget(this);
    commentTable->setColumnCount(5);
    commentTable->setHorizontalHeaderLabels({"ID", "Post", "User", "Content", "Created At"});
    layout->addWidget(commentTable);

    postComboBox = new QComboBox(this);
    layout->addWidget(postComboBox);

    userComboBox = new QComboBox(this);
    layout->addWidget(userComboBox);

    contentEdit = new QLineEdit(this);
    contentEdit->setPlaceholderText("Content");
    layout->addWidget(contentEdit);

    addButton = new QPushButton("Добавть комментарий", this);
    connect(addButton, &QPushButton::clicked, this, &CommentWidget::addComment);
    layout->addWidget(addButton);

    deleteButton = new QPushButton("Удалить комментарий", this);
    connect(deleteButton, &QPushButton::clicked, this, &CommentWidget::deleteComment);
    layout->addWidget(deleteButton);

    // Загрузка постов и пользователей в ComboBox
    QSqlQuery postQuery = db->executeQuery("SELECT post_id, title FROM Posts");
    while (postQuery.next()) {
        postComboBox->addItem(postQuery.value(1).toString(), postQuery.value(0).toInt());
    }

    QSqlQuery userQuery = db->executeQuery("SELECT user_id, username FROM Users");
    while (userQuery.next()) {
        userComboBox->addItem(userQuery.value(1).toString(), userQuery.value(0).toInt());
    }

    loadComments();
}

void CommentWidget::loadComments() {
    commentTable->setRowCount(0);
    QSqlQuery query = db->executeQuery("SELECT c.comment_id, p.title, u.username, c.content, c.created_at FROM Comments c JOIN Posts p ON c.post_id = p.post_id JOIN Users u ON c.user_id = u.user_id");

    while (query.next()) {
        int row = commentTable->rowCount();
        commentTable->insertRow(row);
        commentTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        commentTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        commentTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        commentTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        commentTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
    }
}

void CommentWidget::addComment() {
    int postId = postComboBox->currentData().toInt();
    int userId = userComboBox->currentData().toInt();
    QString content = contentEdit->text();

    if (content.isEmpty()) {
        QMessageBox::warning(this, "Осторожно", "Content не может быть пустым");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Comments (post_id, user_id, content) VALUES (:post_id, :user_id, :content)");
    query.bindValue(":post_id", postId);
    query.bindValue(":user_id", userId);
    query.bindValue(":content", content);

    if (!query.exec()) {
        qDebug() << "Failed to add comment:" << query.lastError().text();
        qDebug() << "Query:" << query.lastQuery();
        qDebug() << "Bound values:" << query.boundValues();
        QMessageBox::critical(this, "Error", "Failed to add comment: " + query.lastError().text());
    } else {
        loadComments();
        contentEdit->clear();
    }
}

void CommentWidget::deleteComment() {
    int row = commentTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Ошибка", "выбирете комментарий для удаления");
        return;
    }

    int id = commentTable->item(row, 0)->text().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM Comments WHERE comment_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete comment: " + query.lastError().text());
    } else {
        loadComments();
    }
}
