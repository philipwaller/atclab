#ifndef INSTRUCTIONTASK_H
#define INSTRUCTIONTASK_H


#include "task.h"


/**
 * @brief The InstructionTask class
 */
class InstructionTask : public Task {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

    friend class InstructionTaskFactory;


private:
    explicit InstructionTask(TaskView *view, const QString & tag = "");


public:
    QString text() { return text_; }
    void setText(QString text) { text_ = text; }


private:
    void initialise();


private:
    QString text_;


};

#endif // INSTRUCTIONTASK_H
