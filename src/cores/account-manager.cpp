#include "account-manager.h"

AccountManager &AccountManager::instance()
{
    static AccountManager instance;
    return instance;
}

void AccountManager::loadAccounts(const QString &owner_id)
{
    this->owner_id = owner_id;
    qDebug() << "loadAccounts by " << owner_id;

    // request to update data to the model.
    if (model) {
        model->fetchData(owner_id);
    }

    // request to update label to the view.
    // emit accountsChanged();
}

QString AccountManager::getOwnerId() const
{
    return owner_id;
}

AccountModel *AccountManager::getModel() const
{
    return model;
}