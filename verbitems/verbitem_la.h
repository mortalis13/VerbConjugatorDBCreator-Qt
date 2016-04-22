#ifndef VERBITEM_LA_H
#define VERBITEM_LA_H


struct VerbItem_LA{

  QString verb;
  
  QStringList lookupWord;

  QStringList impersonalActive;
  QStringList presentIndicativeActive;
  QStringList imperfectIndicativeActive;
  QStringList future1IndicativeActive;
  QStringList perfectIndicativeActive;
  QStringList pluperfectIndicativeActive;
  QStringList future2IndicativeActive;
  QStringList presentConjunctiveActive;

  QStringList imperfectConjunctiveActive;
  QStringList perfectConjunctiveActive;
  QStringList pluperfectConjunctiveActive;
  QStringList impersonalPassive;
  QStringList presentIndicativePassive;
  QStringList imperfectIndicativePassive;
  QStringList future1IndicativePassive;
  QStringList perfectIndicativePassive;
  QStringList pluperfectIndicativePassive;
  QStringList future2IndicativePassive;
  QStringList presentConjunctivePassive;
  QStringList imperfectConjunctivePassive;
  QStringList perfectConjunctivePassive;
  QStringList pluperfectConjunctivePassive;
  QStringList imperativeI;
  QStringList imperativeII;
  QStringList similarVerbs;
  

  void clear(){
    verb.clear();

    lookupWord.clear();

    impersonalActive.clear();
    presentIndicativeActive.clear();
    imperfectIndicativeActive.clear();
    future1IndicativeActive.clear();
    perfectIndicativeActive.clear();
    pluperfectIndicativeActive.clear();
    future2IndicativeActive.clear();
    presentConjunctiveActive.clear();

    imperfectConjunctiveActive.clear();
    perfectConjunctiveActive.clear();
    pluperfectConjunctiveActive.clear();
    impersonalPassive.clear();
    presentIndicativePassive.clear();
    imperfectIndicativePassive.clear();
    future1IndicativePassive.clear();
    perfectIndicativePassive.clear();
    pluperfectIndicativePassive.clear();
    future2IndicativePassive.clear();
    presentConjunctivePassive.clear();
    imperfectConjunctivePassive.clear();
    perfectConjunctivePassive.clear();
    pluperfectConjunctivePassive.clear();
    imperativeI.clear();
    imperativeII.clear();
    similarVerbs.clear();
  }

};

#endif // VERBITEM_LA_H
