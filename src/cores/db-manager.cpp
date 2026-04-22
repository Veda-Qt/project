#include "db-manager.h"
#include <QFile>
#include <QCoreApplication>
#include <QDir>

DbManager &DbManager::instance()
{
    static DbManager instance;
    return instance;
}

DbManager::DbManager(QObject *parent) : QObject(parent)
{
    dbFilePath = QCoreApplication::applicationDirPath() + "/database.json";
    loadDatabase();
}

bool DbManager::insertItem(const QString &table_name, const QJsonObject &item)
{
    QJsonArray table = database.value(table_name).toArray();
    table.append(item);
    database.insert(table_name, table);

    saveDatabase();
    return true;
}

QJsonArray DbManager::selectItems(const QString &table_name, const QJsonObject &conditions)
{
    QJsonArray table = database.value(table_name).toArray();

    if (conditions.isEmpty()) {
        return table;
    }

    QJsonArray result;
    for (const QJsonValue &value : table) {
        QJsonObject item = value.toObject();
        if (matchConditions(item, conditions)) {
            result.append(item);
        }
    }

    return result;
}

bool DbManager::updateItem(const QString &table_name, const QJsonObject &conditions, const QJsonObject &new_data)
{
    QJsonArray table = database.value(table_name).toArray();
    QJsonArray new_table;
    bool isUpdated = false;

    for (const QJsonValue &value : table) {
        QJsonObject item = value.toObject();
        if (matchConditions(item, conditions)) {
            // 조건에 맞는 데이터면, new_data의 값들로 덮어씌움
            for (auto it = new_data.begin(); it != new_data.end(); ++it) {
                item.insert(it.key(), it.value());
            }
            isUpdated = true;
        }
        new_table.append(item);
    }

    if (isUpdated) {
        database.insert(table_name, new_table);
        saveDatabase();
    }

    return isUpdated;
}

bool DbManager::deleteItem(const QString &table_name, const QJsonObject &conditions)
{
    QJsonArray table = database.value(table_name).toArray();
    QJsonArray new_table;
    bool isDeleted = false;

    for (const QJsonValue &value : table) {
        QJsonObject item = value.toObject();
        if (matchConditions(item, conditions)) {
            isDeleted = true;
            continue;
        }
        new_table.append(item);
    }

    if (isDeleted) {
        database.insert(table_name, new_table);
        saveDatabase();
    }

    return isDeleted;
}

void DbManager::loadDatabase()
{
    QFile file(dbFilePath);
    if (!file.exists()) {
        // 파일이 없으면 빈 JSON 객체 반환
        database = QJsonObject();
        return;
    }

    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        database = doc.object();
        file.close();
    }
}

void DbManager::saveDatabase()
{
    QFile file(dbFilePath);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(database);
        file.write(doc.toJson());
        file.close();
    }
}

bool DbManager::matchConditions(const QJsonObject &item, const QJsonObject &conditions) const
{
    for (auto it = conditions.begin(); it != conditions.end(); ++it) {
        if (item.value(it.key()) != it.value()) {
            return false;
        }
    }

    return true;
}