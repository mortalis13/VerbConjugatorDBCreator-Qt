
#include "dbcreator_en.h"


DBCreator_EN::DBCreator_EN() : QThread() {

}


QStringList DBCreator_EN::getFilesInFolder(string path){
  QString dir = QString::fromStdString(path);
  
  QDir qdir(dir);

  QStringList filters;
  filters << "*.txt";

  qdir.setNameFilters(filters);
  qdir.setSorting(QDir::Name | QDir::IgnoreCase);

  return qdir.entryList();
}

void DBCreator_EN::processFile(string path){
  Database_EN* db = new Database_EN();
  verbsList.clear();
  
  qDebug() << "Reading file:" << QString(path.c_str());
  
  fstream textFile(path.c_str(), ios::in);
  if(!textFile.is_open()){
    qDebug() << "EN :: cannot open file:" << QString(path.c_str()) << strerror(errno);
    return;
  }
  
  string str;
  int count = 0;

  while(textFile){
    getline(textFile, str);
    if(!textFile) break;

    currentVerb.clear();

    string article = str.substr(str.find('\t') + 1);
    string cverb = str.substr(0, str.find('\t'));
    QString verb = QString::fromUtf8(cverb.c_str());

    currentVerb.verb = verb;
    

    QWebPage webPage;
    QWebFrame* frame = webPage.mainFrame();

    frame->setHtml(QString::fromStdString(article));
    QWebElement htmlElement = frame->documentElement();

    QWebElement table = htmlElement.findFirst("table");
    QWebElement row = table.findFirst("tr");

    processImpersonalForms(row);

    row = row.nextSibling().nextSibling();
    processIndicative(row);
    processSubjunctive(row);
    
    row = row.nextSibling().nextSibling();
    processConditional(row);
    
    processSimilarVerbs(htmlElement);
    
    
    // QString error = checkVerb(currentVerb);
    // if(error.length() != 0){
    //   error = "verb-error: " + verb + " :: " + error;
    //   qDebug() << error;
    // }
    
    verbsList.append(currentVerb);
  }
  
  db->insertVerbs(verbsList);
  
  textFile.close();
  delete db;
  
  qDebug() << "File Processed:" << QString(path.c_str());
  qDebug();
  // emit updateLog("File Processed: " + QString(path.c_str()));
}

void DBCreator_EN::runProcess(string path, bool useFolder, int startNum){
  // Database_EN* db = new Database_EN();
  // verbsList.clear();
  
  // scanPath = path;
  // this->useFolder = useFolder;
  // start();
  
  
  if(useFolder){
    QStringList filesList = getFilesInFolder(path);

    foreach(QString item, filesList){
      QDir dir(QString(path.c_str()));
      string itemS = (dir.absolutePath() + "/" + item).toStdString();
      processFile(itemS);
    }
  }
  else{
    processFile(path);
  }
  
  
  // qDebug() << "Reading file:" << QString::fromStdString(path);
  
  // fstream textFile(path.c_str(), ios::in);
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
    
  //   processSimilarVerbs(htmlElement);
    
  //   // QString error = checkVerb(currentVerb);
  //   // if(error.length() != 0){
  //   //   error = "verb-error: " + verb + " :: " + error;
  //   //   qDebug() << error;
  //   // }
    
  //   verbsList.append(currentVerb);

  //   if(++count % 100 == 0) qDebug() << count << " items";
  // }
  
  // db->insertVerbs(verbsList);
  
  // textFile.close();
  
  // delete db;

  qDebug() << "Finish";
}


// --------------------------------------------- forms ---------------------------------------------

void DBCreator_EN::processImpersonalForms(const QWebElement& row){
  QWebElement parent = row.findFirst("td").firstChild();              // <td><p>
  currentVerb.impersonalForms = getFormsList(parent);
}


void DBCreator_EN::processIndicative(const QWebElement& row){
  globalRow = row;

  nextRow(true);
  currentVerb.presentIndicative = QStringList() << list1.at(0) << list1.at(2);
  currentVerb.perfectIndicative = QStringList() << list2.at(0) << list2.at(2);

  nextRow();
  currentVerb.pastIndicative = list1.mid(0, 1);
  currentVerb.pluperfectIndicative = list2.mid(0, 1);

  nextRow();
  currentVerb.futureIndicative = list1.mid(0, 1);
  currentVerb.futurePerfectIndicative = list2.mid(0, 1);
}


void DBCreator_EN::processSubjunctive(const QWebElement &row){
  globalRow = row;

  nextRow(true, 1);
  currentVerb.presentSubjunctive = list1.mid(0, 1);
  currentVerb.perfectSubjunctive = list2.mid(0, 1);

  nextRow();
  currentVerb.pastSubjunctive = list1.mid(0, 1);
  currentVerb.pluperfectSubjunctive = list2.mid(0, 1);
}


void DBCreator_EN::processConditional(const QWebElement &row){
  globalRow = row;

  nextRow(true);
  currentVerb.presentConditional = list1.mid(0, 1);
  currentVerb.perfectConditional = list2.mid(0, 1);
}


void DBCreator_EN::processSimilarVerbs(const QWebElement &htmlElement){
  // currentVerb.similarVerbs = "";
}


// ---------------------------------------------  ---------------------------------------------

QStringList DBCreator_EN::getFormsList(const QWebElement& parent){
  QString text = "";
  QStringList list;
  
  QWebElement node = parent.firstChild();
  
  while(!node.isNull()){
    QString tag = node.tagName();
    if(tag == "SPAN"){
      if(text.length() != 0)
        text += "; ";
      text += node.toPlainText();
    }
    else if(tag == "BR" && text.length() != 0){
      list.append(text);
      text.clear();
    }
    node = node.nextSibling();
  }

  if(text.length() != 0){
    list.append(text);
    text.clear();
  }
  
  return list;
}


void DBCreator_EN::nextRow(bool first, int col){
  QWebElement row, td1, td2, cell, parent;
  QWebElementCollection forms, tables;
  // QStringList list1, list2;
  
  if(first){
    cell = globalRow.findFirst("td");
    if(col != 0){
      for(int i=0; i<col; ++i){
        cell = cell.nextSibling();
      }
    }
    globalRow = cell.findFirst("table").findFirst("tr");
  }
  else{
    globalRow = globalRow.nextSibling();
  }
  row = globalRow;

  // listString1.clear();
  // listString2.clear();

  // td1 = row.findFirst("td");
  // td2 = td1.nextSibling();
  
  list1.clear();
  list2.clear();
  
  td1 = row.firstChild();
  td2 = row.lastChild();
  
  tables = td1.findAll("table");
  foreach (QWebElement table, tables){
    parent = table.findFirst("tr").lastChild().firstChild();
    list1 += getFormsList(parent);
  }
  
  tables = td2.findAll("table");
  foreach (QWebElement table, tables){
    parent = table.findFirst("tr").lastChild().firstChild();
    list2 += getFormsList(parent);
  }
  
  // listString1 = list1.join(",");
  // listString2 = list2.join(",");
}

// --------------------------------------------- service ---------------------------------------------

QString DBCreator_EN::checkVerb(VerbItem_EN verb){
  QString error = "";
  
  if(verb.impersonalForms.count() != 3)
    error += " impersonalForms";
  
  if(verb.presentIndicative.count() != 6)
    error += " presentIndicative";
  if(verb.pastIndicative.count() != 6)
    error += " pastIndicative";
  if(verb.futureIndicative.count() != 6)
    error += " futureIndicative";
  if(verb.perfectIndicative.count() != 6)
    error += " perfectIndicative";
  if(verb.pluperfectIndicative.count() != 6)
    error += " pluperfectIndicative";
  if(verb.futurePerfectIndicative.count() != 6)
    error += " futurePerfectIndicative";
  
  if(verb.presentSubjunctive.count() != 6)
    error += " presentSubjunctive";
  if(verb.pastSubjunctive.count() != 6)
    error += " pastSubjunctive";
  if(verb.perfectSubjunctive.count() != 6)
    error += " perfectSubjunctive";
  if(verb.pluperfectSubjunctive.count() != 6)
    error += " pluperfectSubjunctive";
  
  if(verb.presentConditional.count() != 6)
    error += " presentConditional";
  if(verb.perfectConditional.count() != 6)
    error += " perfectConditional";
  
  return error;
}


// --------------------------------------------- thread ---------------------------------------------

void DBCreator_EN::run(){
  if(useFolder){
    QStringList filesList = getFilesInFolder(scanPath);

    foreach(QString item, filesList){
      QDir dir(QString(scanPath.c_str()));
      string itemS = (dir.absolutePath() + "/" + item).toStdString();
      processFile(itemS);
    }
  }
  else{
    processFile(scanPath);
  }
}

void DBCreator_EN::done(){
  qDebug() << "done";
}

