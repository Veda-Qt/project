#include "history-manager.h"

HistoryManager &HistoryManager::instance()
{
    static HistoryManager instance;
    return instance;
}

void HistoryManager::loadHistories(const Account &account)
{
    owner_account = account;

    // request to update data to the model.
    if (model) {
        model->fetchData(account.getNumber());
    }

    // request to update label to the view.
    emit accountChanged(account);
}

Account HistoryManager::getOwnerAccount() const
{
    return owner_account;
}

HistoryModel *HistoryManager::getModel() const
{
    return model;
}