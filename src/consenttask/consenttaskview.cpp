#include "consenttaskview.h"
#include "ui_consenttaskview.h"

ConsentTaskView::ConsentTaskView()
    : TaskView()
    , ui(new Ui::ConsentTaskView)
{
    ui->setupUi(this);
}

ConsentTaskView::~ConsentTaskView()
{
    delete ui;
}

void ConsentTaskView::setText(const QString &text) {
    ui->textEdit->setText(text);
}

void ConsentTaskView::on_acceptBtn_clicked() {
    emit signal_accepted();
}

void ConsentTaskView::on_declineBtn_clicked() {
    emit signal_rejected();
}
