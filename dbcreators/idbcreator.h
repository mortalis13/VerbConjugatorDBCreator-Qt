#ifndef IDBCREATOR_H
#define IDBCREATOR_H

#include <QObject>
#include <QDebug>
#include <QtWebKit>

#include <string>
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;

class IDBCreator : public QObject
{
  Q_OBJECT
  
public:
  explicit IDBCreator(QObject *parent = 0);
  
  virtual void runProcess(string path, bool useFolder = false, int startNum = 0) = 0;
  
  
signals:
  void updateLog(QString text);
  
public slots:
  
};

#endif // IDBCREATOR_H
