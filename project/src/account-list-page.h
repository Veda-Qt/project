#ifndef ACCOUNTLISTPAGE_H
#define ACCOUNTLISTPAGE_H

#include <QWidget>

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

signals:
    void account_selected(int account_id);

private:
    Ui::AccountListPage *ui;
};

#endif // ACCOUNTLISTPAGE_H
