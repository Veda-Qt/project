#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class DbManager : public QObject
{
    Q_OBJECT

public:
    static DbManager &instance();

    // CRUD func
    bool insertItem(const QString &tableName, const QJsonObject &item);
    QJsonArray selectItems(const QString &tableName, const QJsonObject &conditions = QJsonObject());
    bool updateItem(const QString &tableName, const QJsonObject &conditions, const QJsonObject &newData);
    bool deleteItem(const QString &tableName, const QJsonObject &conditions);

private:
    explicit DbManager(QObject *parent = nullptr);
    ~DbManager() = default;

    // JSON 파일 로드, 세이브
    void loadDatabase();
    void saveDatabase();

    // conditions이 아이템 키, 값에 모두 맞는지 확인
    bool matchConditions(const QJsonObject &item, const QJsonObject &conditions) const;

    QString dbFilePath;   // {appDirPath}/database.json
    QJsonObject database; // 메모리에 올려둘 전체 DB 객체
};

#endif // DB_MANAGER_H
