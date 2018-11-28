
#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <iostream>
#include <fstream>
#include <string>

//#include "MultiLepton.cpp"
#include "MEPhaseSpace.cpp"

using namespace std;

class ConfigParser
{
  public:
  ConfigParser();
  ~ConfigParser();

  void LoadConfig(string);
  void GetConfigFromFile(string);
  void GetHypotheses(int*, string**, int**, int**, int**);
 
  void ReadIntegrationRange();
  void ReadJetChoice();
  void ReadOptim();

  ifstream fconf;

  int nHyp;
  string* sHyp;
  int* Hyp;
  int *index_hyp;
/*
  int nhyp;
  string* shyp;
  int* hyp;
  int* nPointsHyp;
  int* index_hyp;
*/
  int doTTLL, doTTHfl, doTTHsl, doTTW, doTTWJJ, doTTbarfl, doTTbarsl, doTLLJ, doWZJJ, doTHJ;
  int nPointsHypTTLL, nPointsHypTTHsl, nPointsHypTTHfl, nPointsHypTTW, nPointsHypTTWJJ, nPointsHypTTbarfl, nPointsHypTTbarsl, nPointsHypTLLJ, nPointsHypWZJJ, nPointsHypTHJ;
  double valJetTFfracmin, valJetTFfracmax, valNeutMaxE;
  string valJetChoice;
  int valOptim, valOptimTopLep, valOptimTopHad, valOptimHiggs, valOptimW;
  double valCsvThresh;
  string valPdf, valMadgraphDir, valTFfile;
  int valGenerator;
  double valComEnergy;
  int valVerbosity;
  int valTFChoice, valTFOption;
  int valDoMinimization;
  int nJetSyst;

  void ReadOptionValue(string*, int*);
  void ReadOptionValue(string*, double*);
  void ReadOptionValue(string*, string*);

  private:
};

ConfigParser::ConfigParser(){
  valVerbosity = 0;
}

void ConfigParser::LoadConfig(string InputFile){

  GetConfigFromFile(InputFile);
  
  ReadIntegrationRange();
  ReadOptim();
  ReadJetChoice();
  return;
}

void ConfigParser::GetConfigFromFile(string InputFile){

  fconf.open(InputFile.c_str());
  string line;
  string option;

  getline(fconf, line);
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &valVerbosity);

  getline(fconf, line); 
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &doTTLL);
  ReadOptionValue(&option, &nPointsHypTTLL);
  ReadOptionValue(&option, &doTTHsl);
  ReadOptionValue(&option, &nPointsHypTTHsl);
  ReadOptionValue(&option, &doTTHfl);
  ReadOptionValue(&option, &nPointsHypTTHfl);
  ReadOptionValue(&option, &doTTW);
  ReadOptionValue(&option, &nPointsHypTTW);
  ReadOptionValue(&option, &doTTWJJ);
  ReadOptionValue(&option, &nPointsHypTTWJJ);
  ReadOptionValue(&option, &doTTbarfl);
  ReadOptionValue(&option, &nPointsHypTTbarfl);
  ReadOptionValue(&option, &doTTbarsl);
  ReadOptionValue(&option, &nPointsHypTTbarsl);
  ReadOptionValue(&option, &doTLLJ);
  ReadOptionValue(&option, &nPointsHypTLLJ);
  ReadOptionValue(&option, &doWZJJ);
  ReadOptionValue(&option, &nPointsHypWZJJ);
  ReadOptionValue(&option, &doTHJ);
  ReadOptionValue(&option, &nPointsHypTHJ);

  ReadOptionValue(&option, &valOptim);
  ReadOptionValue(&option, &valOptimTopHad);
  ReadOptionValue(&option, &valOptimTopLep);
  ReadOptionValue(&option, &valOptimHiggs);
  ReadOptionValue(&option, &valOptimW);
  ReadOptionValue(&option, &valDoMinimization);
  ReadOptionValue(&option, &nJetSyst);

  getline(fconf, line);
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &valJetTFfracmin);
  ReadOptionValue(&option, &valJetTFfracmax);
  ReadOptionValue(&option, &valNeutMaxE);
  ReadOptionValue(&option, &valJetChoice);
  ReadOptionValue(&option, &valCsvThresh);


  getline(fconf, line);
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &valGenerator);
  ReadOptionValue(&option, &valMadgraphDir);
  ReadOptionValue(&option, &valComEnergy);
  ReadOptionValue(&option, &valPdf);

  getline(fconf, line);
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &valTFfile);
  ReadOptionValue(&option, &valTFChoice);
  ReadOptionValue(&option, &valTFOption);

  fconf.close();
  return;
}

ConfigParser::~ConfigParser(){
}

void ConfigParser::ReadOptionValue(string* option, int* value){
  string svalue;
  fconf >> *option;
  fconf >> svalue;
  if (valVerbosity>=1) cout << *option << " "<<svalue << endl;
  *value = atoi(svalue.c_str());
  return;
}

void ConfigParser::ReadOptionValue(string* option, double* value){
  string svalue;
  fconf >> *option;
  fconf >> svalue;
  if (valVerbosity>=1) cout << *option << " "<<svalue << endl;
  *value = atof(svalue.c_str());
  return;
}

void ConfigParser::ReadOptionValue(string* option, string* value){
  string svalue;
  fconf >> *option;
  fconf >> svalue;
  if (valVerbosity>=1) cout << *option << " "<<svalue << endl;
  *value = svalue;
  return;
}

void ConfigParser::GetHypotheses(int* nhyp, string** shyp, int** hyp, int** nPointsHyp, int** index_hyp){

  (*nhyp) = 0;

  if (doTTLL) (*nhyp)++;
  if (doTTHsl) (*nhyp)++;
  if (doTTHfl) (*nhyp)++;
  if (doTTW) (*nhyp)++;
  if (doTTWJJ) (*nhyp)++;
  if (doTTbarfl) (*nhyp)++;
  if (doTTbarsl) (*nhyp)++;
  if (doTLLJ) (*nhyp)++;
  if (doWZJJ) (*nhyp)++;
  if (doTHJ) (*nhyp)++;

  (*shyp) = new string[(*nhyp)];
  (*hyp) = new int[(*nhyp)];
  (*nPointsHyp) = new int[(*nhyp)]; 

  (*index_hyp) = new int[10];
  for (int i=0; i<10; i++) (*index_hyp)[i] = -1;


  int ih=0;
  if (doTTLL){
    (*shyp)[ih] = "TTLL";
    (*hyp)[ih] = kMEM_TTLL_TopAntitopDecay;
    (*nPointsHyp)[ih] = nPointsHypTTLL;
    (*index_hyp)[0] = ih;
    ih++;
  }
  if (doTTHsl){
    (*shyp)[ih] = "TTHsl";
    (*hyp)[ih] = kMEM_TTH_TopAntitopHiggsSemiLepDecay;
    (*nPointsHyp)[ih] = nPointsHypTTHsl;
    (*index_hyp)[1] = ih;
    ih++;
  }
  if (doTTHfl){
    (*shyp)[ih] = "TTHfl";
    (*hyp)[ih] = kMEM_TTH_TopAntitopHiggsDecay;
    (*nPointsHyp)[ih] = nPointsHypTTHfl;
    (*index_hyp)[2] = ih;
    ih++;
  }
  if (doTTW){
    (*shyp)[ih] = "TTW";
    (*hyp)[ih] = kMEM_TTW_TopAntitopDecay;
    (*nPointsHyp)[ih] = nPointsHypTTW;
    (*index_hyp)[3] = ih;
    ih++;
  }
  if (doTTWJJ){
    (*shyp)[ih] = "TTWJJ";
    (*hyp)[ih] = kMEM_TTWJJ_TopAntitopDecay;
    (*nPointsHyp)[ih] = nPointsHypTTWJJ;
    (*index_hyp)[4] = ih;
    ih++;
  }
  if (doTTbarfl){
    (*shyp)[ih] = "TTbarfl";
    (*hyp)[ih] = kMEM_TTbar_TopAntitopFullyLepDecay;
    (*nPointsHyp)[ih] = nPointsHypTTbarfl;
    (*index_hyp)[5] = ih;
    ih++;
  }
  if (doTTbarsl){
    (*shyp)[ih] = "TTbarsl";
    (*hyp)[ih] = kMEM_TTbar_TopAntitopSemiLepDecay;
    (*nPointsHyp)[ih] = nPointsHypTTbarsl;
    (*index_hyp)[6] = ih;
    ih++;
  }
  if (doTLLJ){
    (*shyp)[ih] = "TLLJ";
    (*hyp)[ih] = kMEM_TLLJ_TopLepDecay;
    (*nPointsHyp)[ih] = nPointsHypTLLJ;
    (*index_hyp)[7] = ih;
    ih++;
  }
  if (doWZJJ){
    (*shyp)[ih] = "WZJJ";
    (*hyp)[ih] = kMEM_WZJJ_LepDecay;
    (*nPointsHyp)[ih] = nPointsHypWZJJ;
    (*index_hyp)[8] = ih;
    ih++;
  }
  if (doTHJ){
    (*shyp)[ih] = "THJ";
    (*hyp)[ih] = kMEM_THJ_TopLepDecay;
    (*nPointsHyp)[ih] = nPointsHypTHJ;
    (*index_hyp)[9] = ih;
    ih++;
  }

  if (valVerbosity>=1) {
    for (int ih=0; ih<(*nhyp); ih++) cout << "Will run hyp "<<(*shyp)[ih]<<" code "<<(*hyp)[ih]<<" with "<<(*nPointsHyp)[ih]<<" iterations"<<endl;
  }

  return;
}

void ConfigParser::ReadIntegrationRange(){
  if (valVerbosity>=1) cout << "Integration will use JetTFfracmin="<< valJetTFfracmin<<" JetTFfracmax="<< valJetTFfracmax <<" NeutMaxE="<< valNeutMaxE <<endl;
  return;
}
/*
void ConfigParser::LoadIntegrationRange(double* jetTFfracmin, double* jetTFfracmax, double* neutMaxE){

  *jetTFfracmin = valJetTFfracmin;
  *jetTFfracmax = valJetTFfracmax;
  *neutMaxE = valNeutMaxE;

  cout << "Integration will use JetTFfracmin="<< (*jetTFfracmin)<<" JetTFfracmax="<< (*jetTFfracmax) <<" NeutMaxE="<< (*neutMaxE) <<endl;

  return;
}
*/
void ConfigParser::ReadJetChoice(){
  if (valVerbosity>=1) cout << "In 2j categories, choose 2 jets with option "<< valJetChoice<< endl;
  return;
}
/*
void ConfigParser::LoadJetChoice(string* jetChoice){

  *jetChoice = valJetChoice;
  cout << "In 2j categories, choose 2 jets with option "<< (*jetChoice) << endl;

  return;
}
*/
void ConfigParser::ReadOptim(){

  if (valVerbosity>=1) cout << "Optimizing phase space with option: "<< valOptim <<endl;
  if (valVerbosity>=1) cout << "Optimizing phase space with option: TopHad "<< valOptimTopHad<<", TopLep "<< valOptimTopLep<< ", Higgs "<< valOptimHiggs<< ", Woffshell "<< valOptimW<<endl;

}

/*
void ConfigParser::LoadOptim(int* doOptim){

  *doOptim = valOptim;
  cout << "Optimizing phase space with option: "<< (*doOptim) <<endl;
}

void ConfigParser::LoadOptim(int* doOptimTopHad, int* doOptimTopLep, int* doOptimHiggs, int* doOptimW){

  *doOptimTopHad = valOptimTopHad;
  *doOptimTopLep = valOptimTopLep;
  *doOptimHiggs = valOptimHiggs;
  *doOptimW = valOptimW;

  cout << "Optimizing phase space with option: TopHad "<< (*doOptimTopHad)<<", TopLep "<< (*doOptimTopLep)<< ", Higgs "<< (*doOptimHiggs)<< ", Woffshell "<< (*doOptimW)<<endl;
}
*/

#endif