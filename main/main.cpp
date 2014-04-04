#include <QApplication>

#include "itaskfactory.h"
#include "mainwindow.h"
#include "pluginmanager.h"
#include "statechartbuilder.h"
#include "task.h"
#include "taskview.h"

#include <QAction>
#include <QUuid>
#include <QtDebug>


void set_property(Task* task, const char *key, const QString& value);


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    //
    // Load Plugins
    //

    PluginManager plugins;
    plugins.loadAllPlugins();

    //
    // Build StateChart
    //

    StateChart sm("TheStateChart");
    StateChartBuilder scb(sm);

    QAction *action;

    // Next
    action = new QAction(&w);
    action->setShortcut(Qt::SHIFT + Qt::ALT + Qt::Key_N);
    scb.addStateChartNext(action, SIGNAL(triggered()));
    w.addAction(action);

    // Pause
    action = new QAction(&w);
    action->setShortcut(Qt::SHIFT + Qt::ALT + Qt::Key_P);
    scb.addStateChartPause(action, SIGNAL(triggered()));
    w.addAction(action);

    // Start
    action = new QAction(&w);
    action->setShortcut(Qt::SHIFT + Qt::ALT + Qt::Key_R);
    scb.addStateChartStart(action, SIGNAL(triggered()));
    w.addAction(action);

    // Exit
    action = new QAction(&w);
    action->setShortcut(Qt::SHIFT + Qt::ALT + Qt::Key_X);
    scb.addStateChartExit(action, SIGNAL(triggered()));
    w.addAction(action);


    ITaskFactory *instruction_factory = plugins.lookup("InstructionTask");
    TaskView *instructionView = instruction_factory->createView();
    w.addView(instructionView);

    ITaskFactory *consent_factory = plugins.lookup("ConsentTask");
    TaskView *consentView = consent_factory->createView();
    w.addView(consentView);

    Task* task;

    //
    // INSTRUCTION TASKS
    //

    task = instruction_factory->createTask(instructionView, "Hello");
//    task->setTimeout(5);
    task->setShortcut(Qt::Key_Return);
    task->setProperty("text", "Hello World!");
    scb.addTask(task);

    task = instruction_factory->createTask(instructionView, "Introduction");
    task->setTimeout(5);
    task->setShortcut(Qt::Key_Return);
    task->setProperty("text", "Introduction.....");
    scb.addTask(task);

    task = instruction_factory->createTask(instructionView, "Instruction");
//    task->setTimeout(5);
    task->setShortcut(Qt::Key_Return);
    task->setProperty("text", "Instructions......blah, blah, blah.....");
    scb.addTask(task);

    //
    // CONSENT TASK
    //

    task = consent_factory->createTask(consentView, "!Consent");
    task->setProperty("text", "Sign your life away here?");
    scb.addTask(task);

    QString acceptUuid = QUuid::createUuid().toString();
    QString rejectUuid = QUuid::createUuid().toString();
    set_property(task, "acceptMsg", acceptUuid);
    set_property(task, "rejectMsg", rejectUuid);
    scb.addGuardedTransition(task, acceptUuid, "!Begin");
    scb.addGuardedTransition(task, rejectUuid, "!Thanks");

    //
    //
    //

    task = instruction_factory->createTask(instructionView, "!Begin");
    task->setShortcut(Qt::Key_Return);
    task->setProperty("text", "OK, let us begin!!!");
    scb.addTask(task);

    //
    // Populate Phases
    //

    for (int i = 0; i < 3; ++i) {
        scb.startPhase(QString("PHASE_%1").arg(i, 3,10, QChar('0')));

        for (char j = 'A'; j <= 'C'; ++j) {
            task = instruction_factory->createTask(instructionView, "a_task");
//            task->setTimeout(2);
            task->setShortcut(Qt::Key_Return);
            task->setProperty("text", QString("TASK_%1").arg(j, 3, QChar('o')));
            scb.addTask(task);
        }

        scb.endPhase();
    }

    task = instruction_factory->createTask(instructionView, "!Thanks");
//    task->setTimeout(2);
    task->setShortcut(Qt::Key_Return);
    task->setProperty("text", "Thanks heaps sucker!!!");
    scb.addTask(task);

    scb.build();

    QObject::connect(&sm, &StateChart::finished, &w, &MainWindow::close);

    //
    //
    //

    qDebug() << "--- Start StateMachine (experiment) ---";
    sm.start();
    qDebug() << "--- Show Main Widget (presentation) ---";
    w.show();

    return a.exec();
}

void set_property(Task* task, const char* key, const QString& value) {
    bool success = task->setProperty(key, value);
    if (!success)
            throw;
}
