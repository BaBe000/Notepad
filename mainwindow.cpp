#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    this->setWindowTitle("Notepad of Thainb");
    QAction *saveFile = new QAction(this);
    saveFile->setShortcut(Qt::CTRL + Qt::Key_S);
    QAction *newFile = new QAction(this);
    newFile->setShortcut(Qt::CTRL + Qt::Key_N);

    connect(saveFile, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);
    connect(newFile, &QAction::triggered, this, &MainWindow::on_actionNew_triggered);

    this->addAction(saveFile);
    this->addAction(newFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    filePath = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the file");
    if (fileName == "")
        return;
    QFile file(fileName);
    filePath = fileName;
    this->setWindowTitle(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"..", "file not open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText((text));
    file.close();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionSave_triggered()
{
    if (ui->textEdit->document()->isEmpty() || filePath == "")
        return;
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..", "file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Open the file");
    if (fileName == "")
        return;
    QFile file(fileName);
    filePath = fileName;
    this->setWindowTitle(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..", "file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString aboutNotepad;
    aboutNotepad =   "Author  : Nguyen Ba Thai\n";
    aboutNotepad +=  "Date    : 23/04/2023\n";
    aboutNotepad +=  "(C) NotePad (R)";
    QMessageBox::about(this, "About NotePad", aboutNotepad);
}

