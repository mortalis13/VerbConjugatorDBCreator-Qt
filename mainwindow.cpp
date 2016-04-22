#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QShortcut>
#include <QDebug>
#include <QProcess>

//#include <QtXml>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  // db = NULL;
  // db = new Database();
  
  addActions();
  addShortcuts();
}

MainWindow::~MainWindow()
{
  dbcreator.reset();
  
  delete ui;
  // delete db;
}


void MainWindow::addActions() {
  connect( ui->bRun, SIGNAL(clicked()), this, SLOT(bRunClick()) );
  connect( ui->bTest, SIGNAL(clicked()), this, SLOT(bTestClick()) );
  connect( ui->bTest1, SIGNAL(clicked()), this, SLOT(bTest1Click()) );
}

void MainWindow::addShortcuts() {
  QShortcut *bRun=new QShortcut(QKeySequence("F5"), this);
  connect( bRun, SIGNAL(activated()), ui->bRun, SLOT(click()) );

  QShortcut *quit=new QShortcut(QKeySequence("Esc"), this);
  connect( quit, SIGNAL(activated()), this, SLOT(close()) );
}


// ---------------------------------------------- button handlers / slots ----------------------------------------------

void MainWindow::bTestClick(){
  // Dialog* dialog = new Dialog();
  // dialog->show();
  
  QProcess* prc = new QProcess(this);
  // QString command = "notepad";
  QString command = "cmd.exe";
  prc->startDetached(command);
  
  // prc->waitForStarted();
//  prc->write("path d:/tools\n");
  prc->write("ipconfig\n");
//  prc->write ("exit\n\r");

  prc->closeWriteChannel();

//  system("pause");

  // prc->waitForBytesWritten();
  
  // QProcess::execute(command);
}

void MainWindow::bTest1Click(){
//  QTextStream  out(stdout);
//  int     i;

//  ShowWindow (GetConsoleWindow(),SW_NORMAL);
//  out << endl << "Hello, World" << endl;
//  out << "Application Directory Path:" << endl;
//  out << "Application File Path:" << endl;
//  MessageBox (0,(LPCWSTR)"Continue?",(LPCWSTR)"Silly Question",MB_YESNO);
}

void MainWindow::bRunClick(){
  QString lang = ui->cbLangs->currentText();

  runProcess(lang);
  
  status("Finished");
  
  // listVerbs(2);
  // listVerbs(-1);
}

void MainWindow::updateLog(QString text){
  log(text);
}


// ---------------------------------------------- actions ----------------------------------------------

void MainWindow::runProcess(QString lang){
  
  // unique_ptr<IDBCreator> dbcreator;
  
  if(lang == "English"){
    log("english");
    dbcreator.reset(new DBCreator_EN());
  }
  else if(lang == "French"){
    log("french");
    dbcreator.reset(new DBCreator_FR());
  }
  else if(lang == "German"){
    log("german");
    dbcreator.reset(new DBCreator_DE());
  }
  else if(lang == "Italian"){
    log("italian");
    dbcreator.reset(new DBCreator_IT());
  }
  else if(lang == "Latin"){
    log("latin");
    dbcreator.reset(new DBCreator_LA());
  }
  else if(lang == "Spanish"){
    log("spanish");
    dbcreator.reset(new DBCreator_ES());
  }
  
  // connect( dbcreator.get(), SIGNAL(updateLog(QString)), this, SLOT(updateLog(QString)) );
  
  
  string filesRoot = "files/";
  string fileName = ui->leFilePath->text().toStdString();
  int startNum = ui->leStartNum->text().toInt();
  
  string path = fileName;
  bool useFolder = false;
  
  QString folderPath = ui->leFolderPath->text();
  if(folderPath.trimmed().length() != 0){
    useFolder = true;
    path = folderPath.toStdString();
  }
  
  dbcreator->runProcess(path, useFolder, startNum);
  
  
  // -------------------------------------------
  
  // qDebug();
  
  // Database* db = new Database();
  // verbsList.clear();

  // string filesRoot = "files/";
  // // string fileName = filesRoot + "0.txt";
  // string fileName = filesRoot + ui->leFilePath->text().toStdString();
  
  // qDebug() << "Reading file:" << QString::fromStdString(fileName);
  
  // fstream textFile(fileName.c_str(), ios::in);
  // if(!textFile.is_open()){
  //   cout << "cannot open file\n";
  //   return;
  // }

  // string str;
  // int count = 0;

  // while(textFile){
  //   getline(textFile, str);
  //   if(!textFile) break;

  //   currentVerb.clear();

  //   string article = str.substr(str.find('\t') + 1);
  //   string cverb = str.substr(0, str.find('\t'));
  //   QString verb = QString::fromUtf8(cverb.c_str());

  //   currentVerb.verb = verb;
    

  //   QWebPage webPage;
  //   QWebFrame* frame = webPage.mainFrame();

  //   frame->setHtml(QString::fromStdString(article));
  //   QWebElement htmlElement = frame->documentElement();

  //   QWebElement table = htmlElement.findFirst("table");
  //   QWebElement row = table.findFirst("tr");

  //   processImpersonalForms(row);

  //   row = row.nextSibling().nextSibling();
  //   processIndicative(row);
  //   processSubjunctive(row);
    
  //   row = row.nextSibling().nextSibling();
  //   processConditional(row);
  //   processImperative(row);
    
  //   processSimilarVerbs(htmlElement);
    
  //   QString error = checkVerb(currentVerb);
  //   if(error.length() != 0){
  //     error = "verb-error: " + verb + " :: " + error;
  //     qDebug() << error;
  //   }
    
  //   verbsList.append(currentVerb);

  //   if(++count % 100 == 0) qDebug() << count << " items";
  // }
  
  // db->insertVerbs(verbsList);
  
  // textFile.close();
  // delete db;

  // qDebug() << "Finish";
}


// ---------------------------------------------  ---------------------------------------------

// void MainWindow::processImpersonalForms(const QWebElement& row){
//   QWebElement parent = row.findFirst("td").firstChild();              // <td><p>
//   currentVerb.impersonalForms = getFormsList(parent);
// }


// void MainWindow::processIndicative(const QWebElement& row){
//   globalRow = row;

//   nextRow(true);
//   currentVerb.presentIndicative = list1;
//   currentVerb.preteritPerfectIndicative = list2;

//   nextRow();
//   currentVerb.preteritImperfectIndicative = list1;
//   currentVerb.preteritPluperfectIndicative = list2;

//   nextRow();
//   currentVerb.preteritPerfectSimpleIndicative = list1;
//   currentVerb.preteritPreviuousIndicative = list2;

//   nextRow();
//   currentVerb.futureIndicative = list1;
//   currentVerb.futurePerfectIndicative = list2;
// }


// void MainWindow::processSubjunctive(const QWebElement &row){
//   globalRow = row;

//   nextRow(true, 1);
//   currentVerb.presentSubjunctive = list1;
//   currentVerb.preteritPerfectSubjunctive = list2;

//   nextRow();
//   currentVerb.preteritImperfectSubjunctive = list1;
//   currentVerb.preteritPluperfectSubjunctive = list2;

//   nextRow();
//   currentVerb.futureSubjunctive = list1;
//   currentVerb.futurePerfectSubjunctive = list2;
// }


// void MainWindow::processConditional(const QWebElement &row){
//   globalRow = row;

//   nextRow(true);
//   currentVerb.conditionalSimple = list1;
//   currentVerb.conditionalComplex = list2;
// }


// void MainWindow::processImperative(const QWebElement &row){
//   QWebElement inrow, td, parent;
//   QWebElementCollection forms;
//   QStringList list, tempList;
  
//   inrow = row.findFirst("td").nextSibling().findFirst("table").findFirst("tr");
//   parent = inrow.lastChild().firstChild();
  
//   currentVerb.imperative = getFormsList(parent);
  
//   list.clear();
//   tempList = currentVerb.presentSubjunctive;
//   int len = tempList.count();
//   for(int i=1; i<len; ++i){
//     QString item = tempList[i];
//     list.append("no " + item);
//   }
//   currentVerb.imperativeNegative = list;
// }


// void MainWindow::processSimilarVerbs(const QWebElement &htmlElement){
//   // currentVerb.similarVerbs = "";
// }


// // ---------------------------------------------  ---------------------------------------------

// QStringList MainWindow::getFormsList(const QWebElement& parent){
//   QString text = "";
//   QStringList list;
  
//   QWebElement node = parent.firstChild();
  
//   while(!node.isNull()){
//     QString tag = node.tagName();
//     if(tag == "SPAN"){
//       if(text.length() != 0)
//         text += "; ";
//       text += node.toPlainText();
//     }
//     else if(tag == "BR" && text.length() != 0){
//       list.append(text);
//       text.clear();
//     }
//     node = node.nextSibling();
//   }

//   if(text.length() != 0){
//     list.append(text);
//     text.clear();
//   }
  
//   return list;
// }


// void MainWindow::nextRow(bool first, int col){
//   QWebElement row, td1, td2, cell, parent;
//   QWebElementCollection forms, tables;
//   // QStringList list1, list2;
  
//   if(first){
//     cell = globalRow.findFirst("td");
//     if(col != 0){
//       for(int i=0; i<col; ++i){
//         cell = cell.nextSibling();
//       }
//     }
//     globalRow = cell.findFirst("table").findFirst("tr");
//   }
//   else{
//     globalRow = globalRow.nextSibling();
//   }
//   row = globalRow;

//   // listString1.clear();
//   // listString2.clear();

//   // td1 = row.findFirst("td");
//   // td2 = td1.nextSibling();
  
//   list1.clear();
//   list2.clear();
  
//   td1 = row.firstChild();
//   td2 = row.lastChild();
  
//   tables = td1.findAll("table");
//   foreach (QWebElement table, tables){
//     parent = table.findFirst("tr").lastChild().firstChild();
//     list1 += getFormsList(parent);
//   }
  
//   tables = td2.findAll("table");
//   foreach (QWebElement table, tables){
//     parent = table.findFirst("tr").lastChild().firstChild();
//     list2 += getFormsList(parent);
//   }
  
//   // listString1 = list1.join(",");
//   // listString2 = list2.join(",");
// }


// // --------------------------------------------- service ---------------------------------------------

// QString MainWindow::checkVerb(VerbItem verb){
//   QString error = "";
  
//   if(verb.impersonalForms.count() != 3)
//     error += " impersonalForms";
  
//   if(verb.presentIndicative.count() != 6)
//     error += " presentIndicative";
//   if(verb.preteritImperfectIndicative.count() != 6)
//     error += " preteritImperfectIndicative";
//   if(verb.preteritPerfectSimpleIndicative.count() != 6)
//     error += " preteritPerfectSimpleIndicative";
//   if(verb.futureIndicative.count() != 6)
//     error += " futureIndicative";
//   if(verb.preteritPerfectIndicative.count() != 6)
//     error += " preteritPerfectIndicative";
//   if(verb.preteritPluperfectIndicative.count() != 6)
//     error += " preteritPluperfectIndicative";
//   if(verb.preteritPreviuousIndicative.count() != 6)
//     error += " preteritPreviuousIndicative";
//   if(verb.futurePerfectIndicative.count() != 6)
//     error += " futurePerfectIndicative";
  
//   if(verb.presentSubjunctive.count() != 6)
//     error += " presentSubjunctive";
//   if(verb.preteritPerfectSubjunctive.count() != 6)
//     error += " preteritPerfectSubjunctive";
//   if(verb.preteritImperfectSubjunctive.count() != 12)
//     error += " preteritImperfectSubjunctive";
//   if(verb.preteritPluperfectSubjunctive.count() != 12)
//     error += " preteritPluperfectSubjunctive";
//   if(verb.futureSubjunctive.count() != 6)
//     error += " futureSubjunctive";
//   if(verb.futurePerfectSubjunctive.count() != 6)
//     error += " futurePerfectSubjunctive";
  
//   if(verb.conditionalSimple.count() != 6)
//     error += " conditionalSimple";
//   if(verb.conditionalComplex.count() != 6)
//     error += " conditionalComplex";
  
//   if(verb.imperative.count() != 5)
//     error += " imperative";
//   if(verb.imperativeNegative.count() != 5)
//     error += " imperativeNegative";
  
//   return error;
// }

void MainWindow::logList(QStringList list){
  QPlainTextEdit* log = ui->pteOut;
  foreach(QString item, list)
    log->appendPlainText("  " + item);
  log->appendPlainText("");
}

void MainWindow::logList(QString listString){
  QStringList list = listString.split(",");
  QPlainTextEdit* log = ui->pteOut;
  foreach(QString item, list)
    log->appendPlainText("  " + item);
  log->appendPlainText("");
}

// void MainWindow::listVerbs(int section){
//   QPlainTextEdit* log = ui->pteOut;

//   foreach(VerbItem item, verbsList){
//     if(section == 0 || section == -1){
//       log->appendPlainText(item.verb + "\n");
//       logList(item.impersonalForms);
//     }
//     if(section == 1 || section == -1){
//       logList(item.presentIndicative);
//       logList(item.preteritPerfectIndicative);
//       logList(item.preteritImperfectIndicative);
//       logList(item.preteritPluperfectIndicative);
//       logList(item.preteritPerfectSimpleIndicative);
//       logList(item.preteritPreviuousIndicative);
//       logList(item.futureIndicative);
//       logList(item.futurePerfectIndicative);
//     }
//     if(section == 2 || section == -1){
//       logList(item.presentSubjunctive);
//       logList(item.preteritPerfectSubjunctive);
//       logList(item.preteritImperfectSubjunctive);
//       logList(item.preteritPluperfectSubjunctive);
//       logList(item.futureSubjunctive);
//       logList(item.futurePerfectSubjunctive);
//     }
//     if(section == 3 || section == -1){
//       logList(item.conditionalSimple);
//       logList(item.conditionalComplex);
//     }
//     if(section == 4 || section == -1){
//       logList(item.imperative);
//       logList(item.imperativeNegative);
//     }
//   }

//   log->moveCursor(QTextCursor::Start);
// }

void MainWindow::log(QString text){
  ui->pteOut->appendPlainText(text);
}

void MainWindow::status(QString text){
  ui->statusBar->showMessage(text);
}


// --------------------------------------------- set/get ---------------------------------------------


// --------------------------------------------- add ---------------------------------------------

//void MainWindow::test(){
//  QString fileName;
//  //  fileName = "files/test1.html";
//  fileName = "files/one-line1.html";

//  QWebPage webPage;
//  QWebFrame * frame = webPage.mainFrame();


//  QFile file(fileName);
//  if (!file.open(QIODevice::ReadOnly)){
//    qDebug() << "!file.open()";
//    return;
//  }

//  QByteArray byteArray = file.readAll();
//  QString content(byteArray);

//  frame->setHtml(content);
//  QWebElement htmlElement = frame->documentElement();

//  QWebElement table = htmlElement.findFirst("table");
//  QWebElementCollection rows = table.findAll("tr");
  
//  processImpersonalForms(rows.at(0));

//  // examineChildElements(htmlElement);
//  //  qDebug() << "tag:" << htmlElement.tagName();

//  file.close();
//}


//void MainWindow::examineChildElements(const QWebElement &parentElement)
//{
//  QWebElement element = parentElement.firstChild();
//  while (!element.isNull()) {
//    //        QTreeWidgetItem *item = new QTreeWidgetItem();
//    //        item->setText(0, element.tagName());
//    //        parentItem->addChild(item);

//    QString tag = element.tagName();
//    qDebug() << "tag: " << tag;

//    examineChildElements(element);
//    element = element.nextSibling();
//  }
//}
