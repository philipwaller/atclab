#ifndef ASDTASKVIEW_H
#define ASDTASKVIEW_H

#include "taskview.h"

namespace Ui {
    class AsdTaskView;
}

class AsdTaskView : public TaskView {
    Q_OBJECT

public:
    explicit AsdTaskView();
    ~AsdTaskView();

signals:

public slots:

private:
    Ui::AsdTaskView *ui;

};

#endif // ASDTASKVIEW_H
