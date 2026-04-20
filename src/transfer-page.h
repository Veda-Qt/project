#ifndef TRANSFERPAGE_H
#define TRANSFERPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class TransferPage;
}
QT_END_NAMESPACE

class TransferPage : public QWidget
{
    Q_OBJECT

public:
    explicit TransferPage(QWidget *parent = nullptr);
    ~TransferPage() override;

private:
    Ui::TransferPage *ui;
};

#endif // TRANSFERPAGE_H
