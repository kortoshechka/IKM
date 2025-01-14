#include <QApplication>
#include "mainwindow.h"
#include "database.h"
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Проверка доступности драйверов
    qDebug() << "Available drivers:";
    for (const QString &driver : QSqlDatabase::drivers()) {
        qDebug() << driver;
    }

    // Проверка доступности драйвера QPSQL
    if (!QSqlDatabase::isDriverAvailable("QPSQL")) {
        qDebug() << "QPSQL driver is not available!";
        return -1; // Завершаем программу, если драйвер недоступен
    }

    // Подключение к базе данных
    Database db;
    if (!db.connect()) {
        return -1; // Завершение приложения, если подключение не удалось
    }

    MainWindow w;
    w.show();

    return a.exec();
}
