#include "history-model.h"
#include "../cores/db-manager.h"

HistoryModel::~HistoryModel()
{
    qDeleteAll(histories);
    histories.clear();
}

int HistoryModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : histories.size();
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= histories.size()) {
        return QVariant();
    }

    const History *history = histories.at(index.row());

    switch (role) {
    case ObjectRole:
        return QVariant::fromValue(history);
    case Qt::DisplayRole:
        return QString("%1 %2 %3 | %4원 잔액: %5원").arg(history->getType())
                                                   .arg(history->getOriginName())
                                                   .arg(history->getFormattedTimestamp())
                                                   .arg(history->getAmount())
                                                   .arg(history->getBalance());
    }

    return QVariant();
}

void HistoryModel::fetchData(const QString &number)
{
    beginResetModel();
    qDeleteAll(histories);
    histories.clear();

    QJsonObject conditions;
    conditions["number"] = number;

    const QJsonArray json_histories = DbManager::instance().selectItems("histories", conditions);

    for (const QJsonValue &value : json_histories) {
        QJsonObject obj = value.toObject();

        // watch out to write variable name.
        QString number = obj["number"].toString();
        QString history_id = obj["history_id"].toString();
        QString origin_name = obj["origin_name"].toString();
        QString type = obj["type"].toString(); // 입금 / 출금 / 이체 / 취소
        QString timestamp_str = obj["timestamp"].toString();
        QDateTime timestamp = QDateTime::fromString(timestamp_str, Qt::ISODate);
        if (!timestamp.isValid()) continue;
        long long amount = obj["amount"].toVariant().toLongLong();
        long long balance = obj["balance"].toVariant().toLongLong();

        histories.append(new History(number, history_id, origin_name, type, timestamp, amount, balance));
    }

    endResetModel();
}