#include <QDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      helpDialog{new QMessageBox{QMessageBox::NoIcon,
                                 "Help",
                                 "Enter all the powers using keyboards format.\n"
                                 "For example: '4x^2 - 0x^1 + 6x^0 - 7x^-1' is "
                                 "correct. Make sure to always enter the power of "
                                 "the coefficient even if its 0 or 1. Entering using"
                                 " whitespaces is OKAY.",
                                 QMessageBox::Cancel,
                                 this}},
      m_inputDataHandle{new Gui_app_handler()}{

    ui->setupUi(this);
    QFont font = helpDialog->font();
    font.setPointSize(13);
    helpDialog->setFont(font);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);
    connect(ui->toolButton, &QToolButton::clicked, this, &MainWindow::onToolButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onPushButtonClicked()
{
    m_inputDataHandle->parseInputData(std::move(ui->plainTextEdit_3->toPlainText()),
                                      std::move(ui->plainTextEdit->toPlainText()  ),
                                      std::move(ui->plainTextEdit_2->toPlainText()),
                                      ui->label_5);
}


void MainWindow::onToolButtonClicked()
{
    helpDialog->exec();
}

