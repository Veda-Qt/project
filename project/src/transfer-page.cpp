#include "transfer-page.h"
#include "./ui_transfer-page.h"

TransferPage::TransferPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransferPage)
{
    ui->setupUi(this);
}

TransferPage::~TransferPage()
{
    delete ui;
}