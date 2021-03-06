#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "blinkthread.h"
#include "distancethread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setRange(0, 300);
    ui->progressBar->setFormat("%v cm");
    ui->progressBar->setValue(0);

    BlinkThread *blinkThread = new BlinkThread(15);
    connect(blinkThread, &BlinkThread::ledOn, this, &MainWindow::ledOn);
    connect(blinkThread, &BlinkThread::ledOff, this, &MainWindow::ledOff);
    blinkThread->start();

    DistanceThread *distanceThread = new DistanceThread(28, 29);
    connect(distanceThread, &DistanceThread::distanceUpdated, this, &MainWindow::distanceUpdated);
    distanceThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ledOn()
{
    ui->label->setText("On");
}

void MainWindow::ledOff()
{
    ui->label->setText("Off");
}

void MainWindow::distanceUpdated(double distMeters)
{
    ui->progressBar->setValue(distMeters / 100);
}
