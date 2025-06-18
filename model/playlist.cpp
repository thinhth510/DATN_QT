#include "playlist.h"

Playlist::Playlist(const QString &name, int id)
    : m_name(name)
    , m_id(id)
    , m_createdAt(QDateTime::currentDateTime())
    , m_modifiedAt(QDateTime::currentDateTime())
{
}

Playlist::~Playlist()
{
}

QString Playlist::name() const
{
    return m_name;
}

void Playlist::setName(const QString &name)
{
    m_name = name;
    m_modifiedAt = QDateTime::currentDateTime();
}

QDateTime Playlist::createdAt() const
{
    return m_createdAt;
}

void Playlist::setCreatedAt(const QDateTime &createdAt)
{
    m_createdAt = createdAt;
}

QDateTime Playlist::modifiedAt() const
{
    return m_modifiedAt;
}

void Playlist::setModifiedAt(const QDateTime &modifiedAt)
{
    m_modifiedAt = modifiedAt;
} 
