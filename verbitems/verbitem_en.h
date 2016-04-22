#ifndef VERBITEM_EN_H
#define VERBITEM_EN_H


struct VerbItem_EN{

  QString verb;
  
  QStringList impersonalForms;

  QStringList presentIndicative;
  QStringList pastIndicative;
  QStringList futureIndicative;
  QStringList perfectIndicative;
  QStringList pluperfectIndicative;
  QStringList futurePerfectIndicative;
  QStringList presentSubjunctive;
  QStringList pastSubjunctive;

  QStringList perfectSubjunctive;
  QStringList pluperfectSubjunctive;
  QStringList presentConditional;
  QStringList perfectConditional;
  QStringList similarVerbs;
  

  void clear(){
    verb.clear();

    impersonalForms.clear();

    presentIndicative.clear();
    pastIndicative.clear();
    futureIndicative.clear();
    perfectIndicative.clear();
    pluperfectIndicative.clear();
    futurePerfectIndicative.clear();
    presentSubjunctive.clear();
    pastSubjunctive.clear();

    perfectSubjunctive.clear();
    pluperfectSubjunctive.clear();
    presentConditional.clear();
    perfectConditional.clear();
    similarVerbs.clear();
  }

};

#endif // VERBITEM_EN_H
