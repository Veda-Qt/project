#include "history-model.h"


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
        return QString("%1 %2 %3 | %4 %5").arg(history->getType())
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

    // TODO: fetch data from DB.
    histories.append(new History("1", "333312345", "커피박스", "출금", QDateTime::currentDateTime(), 3000, 25000));
    histories.append(new History("1", "3345342345", "박건영", "입금", QDateTime::currentDateTime(), 5000, 20000));
    histories.append(new History("2", "333312345", "싸다김밥", "출금", QDateTime::currentDateTime(), 5000, 20000));

    endResetModel();
}