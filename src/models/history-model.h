#ifndef HISTORY_MODEL_H
#define HISTORY_MODEL_H

#include <QAbstractListModel>
#include "../cores/history.h"

class HistoryModel : public QAbstractListModel
{
public:
    enum HistoryRoles {};

    explicit HistoryModel(QObject *parent = nullptr) : QAbstractListModel(parent) {};

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<History *> histories;
};

#endif // HISTORY_MODEL_H
