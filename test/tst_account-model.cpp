#include <QtTest>
#include <QSignalSpy>
#include "../src/account-model.h"

class AccountModelTest : public QObject
{
    Q_OBJECT

private slots:
    // 1. 데이터 개수 테스트
    void test_rowCount();
    // 2. DisplayRole 포맷 테스트 (은행명, 잔액 콤마 등)
    void test_dataDisplayRole();
    // 3. 커스텀 Role(Id, Name 등) 테스트
    void test_customRoles();
};

void AccountModelTest::test_rowCount()
{
    AccountModel model;
    QList<Account> list;
    list.append(Account(1, 1000, "테스트1", "111", Account::Bank::KB));
    list.append(Account(2, 2000, "테스트2", "222", Account::Bank::SHINHAN));

    model.setAccounts(list);

    // QCOMPARE(실제값, 기대값)
    QCOMPARE(model.rowCount(), 2);
}

void AccountModelTest::test_dataDisplayRole()
{
    AccountModel model;
    QList<Account> list;
    // 잔액 5000000 -> "5,000,000" 확인용
    list.append(Account(1, 5000000, "내통장", "123-456", Account::Bank::KAKAO));
    model.setAccounts(list);

    QModelIndex index = model.index(0, 0);
    QString data = model.data(index, Qt::DisplayRole).toString();

    // Account::getBankName()과 getFormattedBalance()가 합쳐진 형태를 가정
    // "[카카오뱅크] 내통장 (123-456) - 잔액: 5,000,000원" 형태인지 확인
    QVERIFY(data.contains("카카오뱅크"));
    QVERIFY(data.contains("5,000,000"));
}

void AccountModelTest::test_customRoles()
{
    AccountModel model;
    QList<Account> list;
    list.append(Account(99, 0, "Role테스트", "999", Account::Bank::TOSS));
    model.setAccounts(list);

    QModelIndex index = model.index(0, 0);

    // 우리가 정의한 AccountRoles가 잘 작동하는지 확인
    QCOMPARE(model.data(index, AccountModel::IdRole).toInt(), 99);
    QCOMPARE(model.data(index, AccountModel::NameRole).toString(), QString("Role테스트"));
    QCOMPARE(model.data(index, AccountModel::BankRole).toInt(), static_cast<int>(Account::Bank::TOSS));
}

QTEST_MAIN(AccountModelTest)
#include "tst_account-model.moc"