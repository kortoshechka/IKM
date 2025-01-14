#include "database.h"

Database::Database(QObject *parent) : QObject(parent) {
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("reddit_db");
    db.setUserName("postgres");
    db.setPassword("1488");
}

bool Database::connect() {
    if (!QSqlDatabase::isDriverAvailable("QPSQL")) {
        qDebug() << "QPSQL driver not available!";
        return false;
    }

    qDebug() << "Connecting to database...";
    if (!db.open()) {
        qDebug() << "Error: " << db.lastError().text();
        return false;
    }
    qDebug() << "Connected to database!";
    return true;
}

void Database::disconnect() {
    db.close();
    qDebug() << "Disconnected from database!";
}

QSqlQuery Database::executeQuery(const QString &query, const QVariantList &params) {
    QSqlQuery sqlQuery;
    sqlQuery.prepare(query);
    for (int i = 0; i < params.size(); ++i) {
        sqlQuery.bindValue(i, params[i]);
    }
    if (!sqlQuery.exec()) {
        qDebug() << "Query failed: " << sqlQuery.lastError().text();
    }
    return sqlQuery;
}
