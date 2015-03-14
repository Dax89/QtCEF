#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chromiumwebview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

private slots:
    void on_pbGo_clicked();

private:
        Ui::MainWindow *ui;

        ChromiumWebView* _webview;
};

#endif // MAINWINDOW_H
