#ifndef REMOVE_ACCOUNT_DIALOG_H
#define REMOVE_ACCOUNT_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class RemoveAccountDialog;
}
QT_END_NAMESPACE

class RemoveAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveAccountDialog(QWidget *parent = nullptr);
    ~RemoveAccountDialog() override;

public slots:
    void accept() override;

private:
    Ui::RemoveAccountDialog *ui;
};

#endif // REMOVE_ACCOUNT_DIALOG_H