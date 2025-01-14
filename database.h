#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QVariantList>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    bool connect();
    void disconnect();
    QSqlQuery executeQuery(const QString &query, const QVariantList &params = QVariantList());

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
