#include <QSet>
#include "transfer-model.h"
#include "../cores/db-manager.h"
#include "../cores/transfer-manager.h"

TransferModel::~TransferModel()
{
    qDeleteAll(accounts);
    accounts.clear();
}

int TransferModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : accounts.size();
}

QVariant TransferModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= accounts.size()) {
        return QVariant();
    }

    const Account *account = accounts.at(index.row());

    switch (role) {
    case NumberRole:
        return account->getNumber();
    case OwnerNameRole:
        return account->getOwnerName();
    case BankNameRole:
        return account->getBankName();
    case ObjectRole:
        return QVariant::fromValue(account);
    case Qt::DisplayRole:
        return QString("%1 %2 | (%3)").arg(account->getOwnerName(),
                                         account->getBankName(),
                                         account->getNumber());
    }

    return QVariant();
}

Account TransferModel::getAccount(int row) const
{
    if (row < 0 || row >= accounts.size()) {
        return Account();
    }

    return *(accounts.at(row));
}

void TransferModel::fetchData()
{
    beginResetModel();
    qDeleteAll(accounts);
    accounts.clear();

    QString sender_number = TransferManager::instance().getSenderAccount().getNumber();
    QJsonObject conditions;
    conditions["number"] = sender_number;
    conditions["type"] = "이체";

    const QJsonArray json_recent = DbManager::instance().selectItems("histories", conditions);
    QSet<QString> s_accounts;

    for (int i = json_recent.size() - 1; i >= 0; --i) {
        QJsonObject obj = json_recent[i].toObject();

        QString origin_number = obj["origin_number"].toString();
        QString bank_name = obj["origin_bank_name"].toString();
        QString origin_name = obj["origin_name"].toString();

        if (!s_accounts.contains(origin_number)) {
            s_accounts.insert(origin_number);
            accounts.append(new Account(origin_number, origin_name, bank_name));
        }
    }

    endResetModel();
}