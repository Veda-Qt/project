#ifndef TRANSFER_MODEL_H
#define TRANSFER_MODEL_H

#include <QAbstractListModel>
#include <QList>
#include "../cores/account.h"

class TransferModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum TransferRoles {
        NumberRole = Qt::UserRole + 1,
        OwnerNameRole,
        BankNameRole,
        ObjectRole = Qt::UserRole + 100
    };

    explicit TransferModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    ~TransferModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Account getAccount(int row) const;

public slots:
    void fetchData();

private:
    QList<Account *> accounts;
};

#endif // TRANSFER_MODEL_H