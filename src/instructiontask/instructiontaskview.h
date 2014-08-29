#ifndef INSTRUCTIONTASKVIEW_H
#define INSTRUCTIONTASKVIEW_H


#include "taskview.h"


namespace Ui {
    class InstructionTaskView;
}

class InstructionTaskView : public TaskView
{
    Q_OBJECT

public:
    explicit InstructionTaskView();
    ~InstructionTaskView();

    void setText(const QString &text);

private:
    Ui::InstructionTaskView *ui;
};

#endif // INSTRUCTIONTASKVIEW_H
