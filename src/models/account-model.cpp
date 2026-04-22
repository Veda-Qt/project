#include "account-model.h"
#include "../cores/db-manager.h"

AccountModel::~AccountModel()
{
    qDeleteAll(accounts);
    accounts.clear();
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : accounts.size();
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= accounts.size()) {
        return QVariant();
    }

    const Account *account = accounts.at(index.row());

    switch (role) {
    case ObjectRole:
        return QVariant::fromValue(account);
    case Qt::DisplayRole:
        return QString("%1 %2 | 잔액: %3원").arg(account->getNumber())
                                             .arg(account->getBankName())
                                             .arg(account->getFormattedBalance());
    }

    return QVariant();
}

Account AccountModel::getAccount(int row) const
{
    if (row < 0 || row >= accounts.size()) {
        return Account();
    }

    return *(accounts.at(row));
}

void AccountModel::fetchData(const QString &owner_id)
{
    beginResetModel();
    qDeleteAll(accounts);
    accounts.clear();

    QJsonObject conditions;
    conditions["owner_id"] = owner_id;

    const QJsonArray json_accounts = DbManager::instance().selectItems("accounts", conditions);

    for (const QJsonValue &value : json_accounts) {
        QJsonObject obj = value.toObject();

        // watch out to write variable name.
        QString number = obj["number"].toString();
        QString id = obj["owner_id"].toString();
        QString ownerName = obj["owner_name"].toString();
        QString bankName = obj["bank_name"].toString();
        long long balance = obj["balance"].toVariant().toLongLong();

        accounts.append(new Account(number, id, ownerName, bankName, balance));
    }

    endResetModel();
}