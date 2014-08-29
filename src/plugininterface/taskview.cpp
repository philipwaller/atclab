#include "taskview.h"


#include <QStackedWidget>


TaskView::TaskView() {}

void TaskView::removeActions() {
    removeActions(actions());
}

void TaskView::removeActions(QList<QAction *> actions) {
    foreach (QAction *a, actions) removeAction(a);
}

void TaskView::display() {
    QStackedWidget *stack = qobject_cast<QStackedWidget*>(parent());
    if (!stack) return;
    stack->setCurrentWidget(this);
}
