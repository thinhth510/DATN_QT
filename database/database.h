#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql> // Bao gồm QSqlDatabase, QSqlQuery, QSqlError
#include <QtCore> // Bao gồm QString, QDebug, QFileInfo

class Database {
public:
    Database(const QString &dbPath = "playlist.db");
    ~Database();

    bool open();
    void close();
    bool isOpen() const;
    QSqlDatabase& connection();
    bool initSchema(); // Tạo bảng nếu chưa có

private:
    QSqlDatabase m_db;
    QString m_dbPath;
};

#endif // DATABASE_H 