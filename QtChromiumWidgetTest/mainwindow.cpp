#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbGo_clicked()
{
    QString url = ((ui->leUrl->text().indexOf("http://") == -1) ? ("http://" + ui->leUrl->text()) : ui->leUrl->text());

    ui->webView->load(url);
}
