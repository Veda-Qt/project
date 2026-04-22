#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <QObject>
#include "account.h"
#include "../models/history-model.h"

class HistoryManager : public QObject
{
    Q_OBJECT

public:
    static HistoryManager &instance();

    void loadHistories(const Account &account);
    Account getOwnerAccount() const;
    HistoryModel *getModel() const;

signals:
    void accountChanged(const Account &account);

private:
    explicit HistoryManager(QObject *parent = nullptr) : QObject(parent), model(new HistoryModel(this)) {}

    Account owner_account;
    HistoryModel *model = nullptr;
};

#endif // HISTORY_MANAGER_H
