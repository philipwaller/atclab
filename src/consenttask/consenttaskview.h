#ifndef CONSENTTASKVIEW_H
#define CONSENTTASKVIEW_H

#include "taskview.h"

namespace Ui {
    class ConsentTaskView;
}

class ConsentTaskView : public TaskView
{
    Q_OBJECT

public:
    explicit ConsentTaskView();
    ~ConsentTaskView();

    void setText(const QString &text);

private slots:
    void on_acceptBtn_clicked();
    void on_declineBtn_clicked();

signals:
    void signal_accepted();
    void signal_rejected();

private:
    Ui::ConsentTaskView *ui;
};

#endif // CONSENTTASKVIEW_H
