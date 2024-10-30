#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusLabel.setText("Length: " + QString::number(0) + "   Lines: " + QString::number(0));
    statusLabel.setMaximumWidth(150);

    statusCursorLabel.setText("Ln: " + QString::number(0) + "   Col: " + QString::number(0));
    statusCursorLabel.setMaximumWidth(150);

    autherLabel.setText("陈卓煜");
    autherLabel.setMaximumWidth(150);

    ui->statusbar->addPermanentWidget(&statusLabel);
    ui->statusbar->addPermanentWidget(&statusCursorLabel);
    ui->statusbar->addPermanentWidget(&autherLabel);

}

MainWindow::~MainWindow()
{

    delete ui;
}
