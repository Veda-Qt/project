#include "account-list-page.h"
#include "./ui_account-list-page.h"

AccountListPage::AccountListPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountListPage)
    , model(new AccountModel)
{
    ui->setupUi(this);
    ui->lview_acnt->setModel(model);

    // TODO: fetch Data from FileIO or ServerStream.
    // QList<Account> dataList;
    // dataList = dbManager.fetch();
    // model->setAccounts(dataList);

    // struct DummyAccount { QString name; QString number; int id; };
    // QList<DummyAccount> dummies = {
    //     {"국민은행 보통예금", "123-456-789", 101},
    //     {"신한은행 마이너스통장", "987-654-321", 102},
    //     {"카카오뱅크 세이프박스", "333-222-111", 103}
    // };

    // for (const auto& acc : dummies) {
    //     QStandardItem *item = new QStandardItem(QString("%1 (%2)").arg(acc.name, acc.number));
    //     item->setData(acc.id, Qt::UserRole);
    //     model->appendRow(item);
    // }
}

AccountListPage::~AccountListPage()
{
    delete ui;
}

void AccountListPage::on_lview_acnt_doubleClicked(const QModelIndex &index)
{
    int id = index.data(Qt::UserRole).toInt();
    emit accountSelected(id);
}