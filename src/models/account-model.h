#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>
#include "../cores/account-manager.h"

class AccountModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AccountRoles { IdRole = Qt::UserRole + 1,
                        NumberRole,
                        OwnerNameRole,
                        BankNameRole,
                        BalanceRole };

    explicit AccountModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void updateData();
};

#endif // ACCOUNTMODEL_H
