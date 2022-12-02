#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <speechtotext.h>
#include <QDebug>

bool MainWindow::flag = false;
SpeechToText *workerThread = new SpeechToText;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    workerThread->terminate();
}

void MainWindow::on_btnStartPushButton_clicked()
{
    cout << "Start Thread.." << endl;

    flag = true;

    // Connect our signal and slot
    connect(workerThread, SIGNAL(progressChanged(QString)),
                          SLOT(onProgressChanged(QString)));
    // Setup callback for cleanup when it finishes
    connect(workerThread, SIGNAL(finished()),
            workerThread, SLOT(deleteLater()));
    // Run, Forest, run!
     if(workerThread->isRunning() == false)
        workerThread->start(); // This invokes WorkerThread::run in a new thread
     else cout << "already running.." << endl;
}

void MainWindow::on_btnStopPushButton_clicked()
{
    flag = false;

    cout << "Thread is running.." << endl;
    cout << "But Stop taking input form thread" << endl;

}

void MainWindow::onProgressChanged(QString info)
{
    // akhane ui a data set kora chara
    // onno kono code likha jabe na.

    //ui->voiceTextBrowser->setText(info);
    //ui->voiceTextBrowser->clear();
    ui->voiceTextBrowser->append(info);
}
