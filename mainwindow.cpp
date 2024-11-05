#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <qcolordialog.h>
#include <iostream>
#include <QPlainTextEdit>
#include <QFontDialog>

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

    ui->actionRedo->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

    ischanged = false;
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aboutDialog;
    aboutDialog.exec();
}

void MainWindow::on_actionFind_triggered()
{
    SearchDialog searchDialog;
    searchDialog.exec();
}

void MainWindow::on_actionReplace_triggered()
{
    replaceDialog replacedialog;
    replacedialog.exec();
}

void MainWindow::on_actionNew_triggered()
{

    // 如果已有更改
    if (ischanged)
    {
        QString path = filepath != "" ? filepath : "无标题";
        QMessageBox box(this);
        box.setWindowTitle("文本编辑器");
        box.setIcon(QMessageBox::Question);
        box.setWindowFlag(Qt::Drawer);
        box.setText(QString("你想将更改保存到\n") + path + "吗?");
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        int re = box.exec();
        switch (re)
        {
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;

        case QMessageBox::No:
            break;
        case QMessageBox::Cancel:
            return;
        }
    }

    // 重置编辑器状态
    ui->TextEdit->clear();
    ischanged = false;
    this->setWindowTitle("新建文本文件--编辑器");
    filepath = "";
}

void MainWindow::on_actionOpen_triggered()
{

    if (ischanged)
    {
        QString path = filepath != "" ? filepath : "无标题";
        QMessageBox box(this);
        box.setWindowTitle("文本编辑器");
        box.setIcon(QMessageBox::Question);
        box.setWindowFlag(Qt::Drawer);
        box.setText(QString("你想将更改保存到\n") + path + "吗?");
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        int re = box.exec();
        switch (re)
        {
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;

        case QMessageBox::No:
            break;
        case QMessageBox::Cancel:
            return;
        }
    }

    QString filename = QFileDialog::getOpenFileName(this, "打开文件", ".", tr("Text files (*.txt);;All(*.*)"));
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();
    ui->TextEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());
    filepath = filename;
    ischanged = false;
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(filepath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        on_actionSaveAs_triggered();
        return;
    }
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();

    out << text;
    file.flush();
    file.close();

    ischanged = false;
    this->setWindowTitle(filepath);
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".", tr("Text files (*.txt);;All(*.*)"));
    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }

    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();

    out << text;
    file.flush();
    file.close();

    filepath = filename;
    ischanged = false;
    this->setWindowTitle(filepath);
}

void MainWindow::on_TextEdit_textChanged()
{
    if (ischanged == false)
    {
        ischanged = true;
        this->setWindowTitle("*" + this->windowTitle());
    }
}

void MainWindow::on_actionCut_triggered()
{
    ui->TextEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->TextEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->TextEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->TextEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->TextEdit->undo();
}

void MainWindow::on_TextEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}

void MainWindow::on_TextEdit_redoAvailable(bool b)
{
    ui->actionRedo->setEnabled(b);
}

void MainWindow::on_TextEdit_undoAvailable(bool b)
{
    ui->actionUndo->setEnabled(b);
}

void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    ui->TextEdit->setStyleSheet("color:" + color.name());
}

void MainWindow::on_actionBgColor_triggered()
{

    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    ui->TextEdit->setStyleSheet("background-color:" + color.name());
}


void MainWindow::on_actionLineWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode = ui->TextEdit->lineWrapMode();

    if(mode == QPlainTextEdit::NoWrap){
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        ui->actionLineWrap->setChecked(true);
    }else{
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

        ui->actionLineWrap->setChecked(false);
    }

}


void MainWindow::on_actionFont_2_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok){
        ui->TextEdit->setFont(font);
    }
}


void MainWindow::on_actionShowStatusBar_checkableChanged(bool checkable)
{
    std::cout <<checkable << std::endl;
    if(checkable){

        ui->statusbar->show();
    }
    else{
        ui->statusbar->hide();
    }

}

