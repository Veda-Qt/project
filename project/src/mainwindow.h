#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "account-list-page.h"
#include "account-history-page.h"
#include "transfer-page.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void on_account_clicked(int account_id);

private:
    Ui::MainWindow *ui;
    AccountListPage *account_list_page;
    AccountHistoryPage *account_history_page;
    TransferPage *transfer_page;
};
#endif // MAINWINDOW_H
