#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QShortcut>
#include <QDebug>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  addActions();
  addShortcuts();
}

MainWindow::~MainWindow()
{
  dbcreator.reset();
  delete ui;
}


void MainWindow::addActions() {
  connect( ui->bRun, SIGNAL(clicked()), this, SLOT(bRunClick()) );
  connect( ui->bTest, SIGNAL(clicked()), this, SLOT(bTestClick()) );
  connect( ui->bTest1, SIGNAL(clicked()), this, SLOT(bTest1Click()) );
}

void MainWindow::addShortcuts() {
  QShortcut *bRun = new QShortcut(QKeySequence("F5"), this);
  connect( bRun, SIGNAL(activated()), ui->bRun, SLOT(click()) );

  QShortcut *quit = new QShortcut(QKeySequence("Esc"), this);
  connect( quit, SIGNAL(activated()), this, SLOT(close()) );
}


// ---------------------------------------------- button handlers / slots ----------------------------------------------

void MainWindow::bTestClick() {
  // Dialog* dialog = new Dialog();
  // dialog->show();
  
  QProcess* prc = new QProcess(this);
  // QString command = "notepad";
  QString command = "cmd.exe";
  prc->startDetached(command);
  
  // prc->waitForStarted();
  // prc->write("path d:/tools\n");
  prc->write("ipconfig\n");
  // prc->write ("exit\n\r");

  prc->closeWriteChannel();

  // system("pause");
  // prc->waitForBytesWritten();
  // QProcess::execute(command);
}

void MainWindow::bTest1Click() {
  // QTextStream out(stdout);
  // int i;

  // ShowWindow (GetConsoleWindow(),SW_NORMAL);
  // out << endl << "Hello, World" << endl;
  // out << "Application Directory Path:" << endl;
  // out << "Application File Path:" << endl;
  // MessageBox (0,(LPCWSTR)"Continue?",(LPCWSTR)"Silly Question",MB_YESNO);
}

void MainWindow::bRunClick() {
  QString lang = ui->cbLangs->currentText();
  runProcess(lang);
  status("Finished");
}

void MainWindow::updateLog(QString text) {
  log(text);
}


// ---------------------------------------------- actions ----------------------------------------------

void MainWindow::runProcess(QString lang) {
  if (lang == "English") {
    log("english");
    dbcreator.reset(new DBCreator_EN());
  }
  else if (lang == "French") {
    log("french");
    dbcreator.reset(new DBCreator_FR());
  }
  else if (lang == "German") {
    log("german");
    dbcreator.reset(new DBCreator_DE());
  }
  else if (lang == "Italian") {
    log("italian");
    dbcreator.reset(new DBCreator_IT());
  }
  else if (lang == "Latin") {
    log("latin");
    dbcreator.reset(new DBCreator_LA());
  }
  else if (lang == "Spanish") {
    log("spanish");
    dbcreator.reset(new DBCreator_ES());
  }
  
  string filesRoot = "files/";
  string fileName = ui->leFilePath->text().toStdString();
  int startNum = ui->leStartNum->text().toInt();
  
  string path = fileName;
  bool useFolder = false;
  
  QString folderPath = ui->leFolderPath->text();
  if (folderPath.trimmed().length() != 0) {
    useFolder = true;
    path = folderPath.toStdString();
  }
  
  dbcreator->runProcess(path, useFolder, startNum);
}


void MainWindow::logList(QStringList list) {
  QPlainTextEdit* log = ui->pteOut;
  foreach (QString item, list)
    log->appendPlainText("  " + item);
  log->appendPlainText("");
}

void MainWindow::logList(QString listString) {
  QStringList list = listString.split(",");
  QPlainTextEdit* log = ui->pteOut;
  foreach (QString item, list)
    log->appendPlainText("  " + item);
  log->appendPlainText("");
}

void MainWindow::log(QString text) {
  ui->pteOut->appendPlainText(text);
}

void MainWindow::status(QString text) {
  ui->statusBar->showMessage(text);
}
