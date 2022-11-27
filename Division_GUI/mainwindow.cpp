#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

