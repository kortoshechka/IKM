#include "userwidget.h"

UserWidget::UserWidget(Database *db, QWidget *parent)
    : QWidget(parent), db(db)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    userTable = new QTableWidget(this);
    userTable->setColumnCount(3);
    userTable->setHorizontalHeaderLabels({"ID", "Username", "Email"});
    layout->addWidget(userTable);

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");
    layout->addWidget(usernameEdit);

    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Email");
    layout->addWidget(emailEdit);

    addButton = new QPushButton("Добавить пользователя", this);
    connect(addButton, &QPushButton::clicked, this, &UserWidget::addUser);
    layout->addWidget(addButton);

    deleteButton = new QPushButton("Удалить пользователя", this);
    connect(deleteButton, &QPushButton::clicked, this, &UserWidget::deleteUser);
    layout->addWidget(deleteButton);

    loadUsers();
}

void UserWidget::loadUsers() {
    userTable->setRowCount(0);
    QSqlQuery query = db->executeQuery("SELECT * FROM Users");

    while (query.next()) {
        int row = userTable->rowCount();
        userTable->insertRow(row);
        userTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        userTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        userTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
    }
}

void UserWidget::addUser() {
    QString username = usernameEdit->text();
    QString email = emailEdit->text();

    if (username.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Осторожно", "Username и email не могут быть пустыми!");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Users (username, email) VALUES (:username, :email)");
    query.bindValue(":username", username);
    query.bindValue(":email", email);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to add user: " + query.lastError().text());
    } else {
        loadUsers();
        usernameEdit->clear();
        emailEdit->clear();
    }
}

void UserWidget::deleteUser() {
    int row = userTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Осторожно", "Выбирете пользователя для удаления!");
        return;
    }

    int id = userTable->item(row, 0)->text().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM Users WHERE user_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete user: " + query.lastError().text());
    } else {
        loadUsers();
    }
}
