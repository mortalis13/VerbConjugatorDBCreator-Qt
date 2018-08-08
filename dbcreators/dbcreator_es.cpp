
#include "dbcreator_es.h"

DBCreator_ES::DBCreator_ES(){

}


QStringList DBCreator_ES::getFilesInFolder(string path){
  QString dir = QString::fromStdString(path);
  
  QDir qdir(dir);

  QStringList filters;
  filters << "*.txt";

  qdir.setNameFilters(filters);
  qdir.setSorting(QDir::Name | QDir::IgnoreCase);

  return qdir.entryList();
}

void DBCreator_ES::processFile(string path){
  Database_ES* db = new Database_ES();
  verbsList.clear();
  
  qDebug() << "Reading file:" << QString(path.c_str());
  
  fstream textFile(path.c_str(), ios::in);
  if(!textFile.is_open()){
    qDebug() << "ES :: cannot open file:" << QString(path.c_str()) << strerror(errno);
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
    processImperative(row);
    
    processSimilarVerbs(htmlElement);
    
    verbsList.append(currentVerb);
  }
  
  db->insertVerbs(verbsList);
  
  textFile.close();
  delete db;
  
  qDebug() << "File Processed:" << QString(path.c_str());
  qDebug();
}

void DBCreator_ES::runProcess(string path, bool useFolder, int startNum){
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
  
  qDebug() << "Finish";
}


// --------------------------------------------- forms ---------------------------------------------

void DBCreator_ES::processImpersonalForms(const QWebElement& row){
  QWebElement parent = row.findFirst("td").firstChild();              // <td><p>
  currentVerb.impersonalForms = getFormsList(parent);
}


void DBCreator_ES::processIndicative(const QWebElement& row){
  globalRow = row;

  nextRow(true);
  currentVerb.presentIndicative = list1;
  currentVerb.preteritPerfectIndicative = list2;

  nextRow();
  currentVerb.preteritImperfectIndicative = list1;
  currentVerb.preteritPluperfectIndicative = list2;

  nextRow();
  currentVerb.preteritPerfectSimpleIndicative = list1;
  currentVerb.preteritPreviuousIndicative = list2;

  nextRow();
  currentVerb.futureIndicative = list1;
  currentVerb.futurePerfectIndicative = list2;
}


void DBCreator_ES::processSubjunctive(const QWebElement &row){
  globalRow = row;

  nextRow(true, 1);
  currentVerb.presentSubjunctive = list1;
  currentVerb.preteritPerfectSubjunctive = list2;

  nextRow();
  currentVerb.preteritImperfectSubjunctive = list1;
  currentVerb.preteritPluperfectSubjunctive = list2;

  nextRow();
  currentVerb.futureSubjunctive = list1;
  currentVerb.futurePerfectSubjunctive = list2;
}


void DBCreator_ES::processConditional(const QWebElement &row){
  globalRow = row;

  nextRow(true);
  currentVerb.conditionalSimple = list1;
  currentVerb.conditionalComplex = list2;
}

void DBCreator_ES::processImperative(const QWebElement &row){
  QWebElement inrow, td, parent;
  QWebElementCollection forms;
  QStringList list, tempList;
  
  inrow = row.findFirst("td").nextSibling().findFirst("table").findFirst("tr");
  parent = inrow.lastChild().firstChild();
  
  currentVerb.imperative = getFormsList(parent);
  
  list.clear();
  tempList = currentVerb.presentSubjunctive;
  int len = tempList.count();
  for(int i=1; i<len; ++i){
    QString item = tempList[i];
    list.append("no " + item);
  }
  currentVerb.imperativeNegative = list;
}


void DBCreator_ES::processSimilarVerbs(const QWebElement &htmlElement){
  // currentVerb.similarVerbs = "";
}


// ---------------------------------------------  ---------------------------------------------

QStringList DBCreator_ES::getFormsList(const QWebElement& parent){
  QString text = "";
  QStringList list;
  
  QWebElement node = parent.firstChild();
  
  while(!node.isNull()){
    QString tag = node.tagName();
    if(tag == "SPAN"){
      if(text.length() != 0)
        text += "; ";
      text += node.toPlainText().trimmed();
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


void DBCreator_ES::nextRow(bool first, int col){
  QWebElement row, td1, td2, cell, parent;
  QWebElementCollection forms, tables;
  
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
}

// --------------------------------------------- service ---------------------------------------------

QString DBCreator_ES::checkVerb(VerbItem_ES verb){
  QString error = "";
  
  return error;
}


// --------------------------------------------- thread ---------------------------------------------

void DBCreator_ES::run(){
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

void DBCreator_ES::done(){
  qDebug() << "done";
}

