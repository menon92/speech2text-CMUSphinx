#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        static bool flag;

    // Define slot:
    public slots:
        void onProgressChanged(QString info);

    private slots:
        void on_btnStartPushButton_clicked();

        void on_btnStopPushButton_clicked();

    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
