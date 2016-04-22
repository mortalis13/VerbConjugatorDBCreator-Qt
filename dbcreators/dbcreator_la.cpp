
#include "dbcreator_la.h"


DBCreator_LA::DBCreator_LA(){

}


QStringList DBCreator_LA::getFilesInFolder(string path){
  QString dir = QString::fromStdString(path);
  
  QDir qdir(dir);

  QStringList filters;
  filters << "*.txt";

  qdir.setNameFilters(filters);
  qdir.setSorting(QDir::Name | QDir::IgnoreCase);

  return qdir.entryList();
}

void DBCreator_LA::processFile(string path){
  Database_LA* db = new Database_LA();
  verbsList.clear();
  
  qDebug() << "Reading file:" << QString(path.c_str());
  
  fstream textFile(path.c_str(), ios::in);
  if(!textFile.is_open()){
    qDebug() << "LA :: cannot open file:" << QString(path.c_str()) << strerror(errno);
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

    processLookupWord(row);
    
    row = row.nextSibling().nextSibling();
    processImpersonalForms(row);

    row = row.nextSibling();
    processActive(row);
    processPassive(row);
    
    row = row.nextSibling().nextSibling();
    processImperative(row);
    
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
}

void DBCreator_LA::runProcess(string path, bool useFolder, int startNum){
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

void DBCreator_LA::processLookupWord(const QWebElement& row){
  QWebElement parent = row.findFirst("td").firstChild();              // <td><p>
  currentVerb.lookupWord = getFormsList(parent);
}

void DBCreator_LA::processImpersonalForms(const QWebElement& row){
  QWebElement parent = row.findFirst("td").firstChild();              // <td><p>
  currentVerb.impersonalActive = getFormsList(parent);
  
  parent = row.findFirst("td").nextSibling().firstChild();              // <td><p>
  currentVerb.impersonalPassive = getFormsList(parent);
}

void DBCreator_LA::processActive(const QWebElement& row){
  // QWebElement activeRow = row.findFirst("td").findFirst("table").findFirst("tr").nextSibling();
  // globalRow = activeRow;
  
  globalRow = row;

  nextRow(true);
  currentVerb.presentIndicativeActive = list1;
  currentVerb.presentConjunctiveActive = list2;

  nextRow();
  currentVerb.imperfectIndicativeActive = list1;
  currentVerb.imperfectConjunctiveActive = list2;

  nextRow();
  currentVerb.future1IndicativeActive = list1;

  nextRow();
  currentVerb.perfectIndicativeActive = list1;
  currentVerb.perfectConjunctiveActive = list2;

  nextRow();
  currentVerb.pluperfectIndicativeActive = list1;
  currentVerb.pluperfectConjunctiveActive = list2;

  nextRow();
  currentVerb.future2IndicativeActive = list1;
}

void DBCreator_LA::processPassive(const QWebElement& row){
  // QWebElement passiveRow = row.findFirst("td").nextSibling().findFirst("table").findFirst("tr").nextSibling();
  // globalRow = passiveRow;
  
  globalRow = row;

  nextRow(true, 1);
  currentVerb.presentIndicativePassive = list1;
  currentVerb.presentConjunctivePassive = list2;

  nextRow();
  currentVerb.imperfectIndicativePassive = list1;
  currentVerb.imperfectConjunctivePassive = list2;

  nextRow();
  currentVerb.future1IndicativePassive = list1;

  nextRow();
  currentVerb.perfectIndicativePassive = list1;
  currentVerb.perfectConjunctivePassive = list2;

  nextRow();
  currentVerb.pluperfectIndicativePassive = list1;
  currentVerb.pluperfectConjunctivePassive = list2;

  nextRow();
  currentVerb.future2IndicativePassive = list1;
}


void DBCreator_LA::processImperative(const QWebElement &row){
  QWebElement inrow, td, parent, td1, td2, imperativeIRow, imperativeIIRow;
  QStringList tempList;
  
  inrow = row.findFirst("td").findFirst("table").findFirst("tr");
  td1 = inrow.firstChild();
  td2 = inrow.lastChild();
  
  imperativeIRow = td1.findFirst("table").findFirst("tr");
  parent = imperativeIRow.lastChild().firstChild();
  
  tempList = getFormsList(parent);
  for(int i=0; i<tempList.size(); ++i){
    if(tempList.at(i).length() == 0){
      tempList.removeAt(i);
    }
  }
  
  currentVerb.imperativeI = tempList;
  
  
  imperativeIIRow = td2.findFirst("table").findFirst("tr");
  parent = imperativeIIRow.lastChild().firstChild();
  
  tempList.clear();
  tempList = getFormsList(parent);
  for(int i=0; i<tempList.size(); ++i){
    if(tempList.at(i).length() == 0){
      tempList.removeAt(i);
    }
  }
  
  currentVerb.imperativeII = tempList;
}


void DBCreator_LA::processSimilarVerbs(const QWebElement &htmlElement){
  // currentVerb.similarVerbs = "";
}


// ---------------------------------------------  ---------------------------------------------

QStringList DBCreator_LA::getFormsList(const QWebElement& parent){
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


void DBCreator_LA::nextRow(bool first, int col){
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
    globalRow = cell.findFirst("table").findFirst("tr").nextSibling();
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

// QString DBCreator_LA::checkVerb(VerbItem_LA verb){
//   QString error = "";
  
//   if(verb.impersonalForms.count() != 3)
//     error += " impersonalForms";
  
//   if(verb.presentIndicative.count() != 6)
//     error += " presentIndicative";
//   if(verb.preteritIndicative.count() != 6)
//     error += " preteritIndicative";
//   if(verb.futureIndicative.count() != 6)
//     error += " futureIndicative";
//   if(verb.perfectIndicative.count() != 6)
//     error += " perfectIndicative";
//   if(verb.pluperfectIndicative.count() != 6)
//     error += " pluperfectIndicative";
//   if(verb.futurePerfectIndicative.count() != 6)
//     error += " futurePerfectIndicative";
  
//   if(verb.presentSubjunctive.count() != 6)
//     error += " presentSubjunctive";
//   if(verb.preteritSubjunctive.count() != 6)
//     error += " preteritSubjunctive";
//   if(verb.perfectSubjunctive.count() != 6)
//     error += " perfectSubjunctive";
//   if(verb.pluperfectSubjunctive.count() != 6)
//     error += " pluperfectSubjunctive";
  
//   if(verb.presentConditional.count() != 6)
//     error += " presentConditional";
//   if(verb.perfectConditional.count() != 6)
//     error += " perfectConditional";
  
//   return error;
// }


// --------------------------------------------- thread ---------------------------------------------

void DBCreator_LA::run(){
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

void DBCreator_LA::done(){
  qDebug() << "done";
}

