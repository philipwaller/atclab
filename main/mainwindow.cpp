#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addView(QWidget *task) {
    ui->stackedWidget->addWidget(task);
}

void MainWindow::setStatus(const QString &status) {
    ui->statusBar->showMessage(tr(status.toLocal8Bit()));
}
