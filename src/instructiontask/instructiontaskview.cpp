#include "instructiontaskview.h"
#include "ui_instructiontaskview.h"

InstructionTaskView::InstructionTaskView() :
    TaskView(),
    ui(new Ui::InstructionTaskView)
{
    ui->setupUi(this);
}

InstructionTaskView::~InstructionTaskView()
{
    delete ui;
}

void InstructionTaskView::setText(const QString &text) {
    ui->content->setText(text);
}
