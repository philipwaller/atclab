#include "asdtaskview.h"
#include "ui_asdtaskview.h"

AsdTaskView::AsdTaskView()
        : TaskView()
        , ui(new Ui::AsdTaskView)
{
    ui->setupUi(this);
}

AsdTaskView::~AsdTaskView() {
    delete ui;
}
