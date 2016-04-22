#ifndef VERBITEM_IT_H
#define VERBITEM_IT_H


struct VerbItem_IT{

  QString verb;
  
  QStringList impersonalForms;

  QStringList presentIndicative;
  QStringList imperfectIndicative;
  QStringList futureIndicative;
  QStringList pastRemoteIndicative;
  QStringList pastIndicative;
  QStringList pluperfectIndicative;
  QStringList futurePerfectIndicative;
  QStringList pluperfectRemoteIndicative;

  QStringList presentSubjunctive;
  QStringList imperfectSubjunctive;
  QStringList pastSubjunctive;
  QStringList pluperfectSubjunctive;
  QStringList presentConditional;
  QStringList pastConditional;
  QStringList imperative;
  QStringList similarVerbs;
  

  void clear(){
    verb.clear();

    impersonalForms.clear();

    presentIndicative.clear();
    imperfectIndicative.clear();
    futureIndicative.clear();
    pastRemoteIndicative.clear();
    pastIndicative.clear();
    pluperfectIndicative.clear();
    futurePerfectIndicative.clear();
    pluperfectRemoteIndicative.clear();

    presentSubjunctive.clear();
    imperfectSubjunctive.clear();
    pastSubjunctive.clear();
    pluperfectSubjunctive.clear();
    presentConditional.clear();
    pastConditional.clear();
    imperative.clear();
    similarVerbs.clear();
  }

};

#endif // VERBITEM_IT_H
