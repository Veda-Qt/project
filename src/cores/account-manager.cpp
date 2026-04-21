#include "account-manager.h"

AccountManager::~AccountManager()
{
    qDeleteAll(accounts);
}

AccountManager &AccountManager::instance()
{
    static AccountManager instance;
    return instance;
}

void AccountManager::loadAccounts()
{
    qDeleteAll(accounts);
    accounts.clear();

    // TODO: fetch data
    accounts.append(new Account("qwer123", "333312345", "박건영", "국민은행", 50000000));
    accounts.append(new Account("asdf777", "3345342345", "박건영", "토스은행", 10000));
    accounts.append(new Account("gusese", "3212345", "홍진기", "우리은행", 23243513));

    emit accountsChanged();
}

void AccountManager::addAccount(Account *account)
{

}