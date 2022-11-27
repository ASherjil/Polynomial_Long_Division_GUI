#include <QDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), helpDialog{new QMessageBox{QMessageBox::NoIcon,
                                                         "Help",
                                                         "Enter all the powers using keyboards format.\n"
                                                         "For example: '4x^2 - 5x^1 + 6x^0 - 7x^-1' is "
                                                         "correct. Make sure to always enter the power of "
                                                         "the coefficient even if its 0 or 1. Entering using"
                                                         " whitespaces is OKAY.",
                                                        QMessageBox::Cancel,
                                                        this}}
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    m_inputDataHandle.parseInputData(std::move(ui->plainTextEdit_3->toPlainText()),
                                     std::move(ui->plainTextEdit->toPlainText()  ),
                                     std::move(ui->plainTextEdit_2->toPlainText()));
}


void MainWindow::on_toolButton_clicked()
{
    helpDialog->exec();
}

