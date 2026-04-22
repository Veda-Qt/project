#include "transfer-manager.h"

TransferManager &TransferManager::instance()
{
    static TransferManager instance;
    return instance;
}

TransferModel *TransferManager::getModel() const
{
    return model;
}

void TransferManager::setSenderAccount(const Account &account)
{
    sender_account = account;
}

void TransferManager::loadRecentTransfers()
{
    if (model) {
        model->fetchData();
    }
}

void TransferManager::requestTransfer(const QString &target_number, long long amount)
{
    qDebug() << "request transfer from " << sender_account.getNumber()
             << " -> to " << target_number
             << " | amount: " << amount;

    if (sender_account.getNumber() == target_number) {
        emit transferFailed("출금 계좌와 입금 계좌가 동일합니다.");
        return;
    }
    if (sender_account.getBalance() < amount) {
        emit transferFailed("계좌의 잔액이 부족합니다.");
        return;
    }

    // -------------------------------------------------------------
    // TODO: 실제 DB 트랜잭션(Transaction)
    // 1. 출금 계좌 잔액 감소 (UPDATE)
    // 2. 입금 계좌 잔액 증가 (UPDATE)
    // 3. 거래 내역 테이블에 출금 기록 추가 (INSERT)
    // 4. 거래 내역 테이블에 입금 기록 추가 (INSERT)
    // (이 4가지 과정이 모두 성공해야만 이체 성공으로 간주)
    // -------------------------------------------------------------

    // TEST: 임시 성공 처리
    bool isDbSuccess = true;

    if (isDbSuccess) {
        emit transferSuccess();
    } else {
        emit transferFailed("서버 오류로 이체에 실패했습니다.");
    }
}