#ifndef HISTORY_MODEL_H
#define HISTORY_MODEL_H

#include <QAbstractListModel>
#include <QModelIndex>
#include "../cores/history.h"

class HistoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum HistoryRoles {
        NumberRole = Qt::UserRole + 1,
        HistoryIdRole,
        OriginNameRole,
        TypeRole,
        TimeRole,
        AmountRole,
        BalanceRole,
        ObjectRole = Qt::UserRole + 100
    };

    explicit HistoryModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    ~HistoryModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void fetchData(const QString &number);

private:
    QList<History *> histories;
};

#endif // HISTORY_MODEL_H
