#include "database.h"

Database::Database(const QString &dbPath)
    : m_dbPath(dbPath)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_dbPath);
}

Database::~Database() {
    close();
}

bool Database::open() {
    if (!m_db.isOpen()) {
        qDebug() << "[Database] Absolute path:" << QFileInfo(m_dbPath).absoluteFilePath();
        if (!m_db.open()) {
            qWarning() << "Cannot open database:" << m_db.lastError().text();
            return false;
        }
    }
    return true;
}

void Database::close() {
    if (m_db.isOpen()) m_db.close();
}

bool Database::isOpen() const {
    return m_db.isOpen();
}

QSqlDatabase& Database::connection() {
    return m_db;
}

bool Database::initSchema() {
    QSqlQuery query(m_db);
    // Bảng playlists
    QString createPlaylists = R"(
        CREATE TABLE IF NOT EXISTS playlists (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            created_at TEXT,
            modified_at TEXT
        )
    )";
    if (!query.exec(createPlaylists)) {
        qWarning() << "Create playlists table failed:" << query.lastError().text();
        return false;
    }
    // Bảng media_files
    QString createMediaFiles = R"(
        CREATE TABLE IF NOT EXISTS media_files (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            playlist_id INTEGER,
            path TEXT,
            title TEXT,
            artist TEXT,
            album TEXT,
            composer TEXT,
            duration INTEGER,
            genre TEXT,
            size INTEGER,
            FOREIGN KEY(playlist_id) REFERENCES playlists(id) ON DELETE CASCADE
        )
    )";
    if (!query.exec(createMediaFiles)) {
        qWarning() << "Create media_files table failed:" << query.lastError().text();
        return false;
    }
    return true;
} 