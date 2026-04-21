#ifndef ACCOUNTLISTPAGE_H
#define ACCOUNTLISTPAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include "../models/account-model.h"
#include "../cores/account-manager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AccountListPage;
}
QT_END_NAMESPACE;

class AccountListPage : public QWidget
{
    Q_OBJECT

public:
    explicit AccountListPage(QWidget *parent = nullptr);
    ~AccountListPage() override;

    QAbstractItemModel *getModel() const;

signals:
    void accountSelected(int account_id);

private slots:
    void on_lview_acnt_doubleClicked(const QModelIndex &index);

private:
    Ui::AccountListPage *ui;
    AccountModel *model;
};

#endif // ACCOUNTLISTPAGE_H
