
#ifndef CONFIGPARSER_CPP
#define CONFIGPARSER_CPP

#include <iostream>
#include <fstream>
#include <string>

#include "../interface/ConfigParser.h"
#include "../interface/MEPhaseSpace.h"

#if defined(__OPTIMIZE__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <boost/algorithm/string.hpp>
#if defined(__OPTIMIZE__)
#pragma GCC diagnostic pop
#endif

using namespace std;

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

  ConfigParser::SubstituteEnv(valMadgraphDir);
  ConfigParser::SubstituteEnv(valTFfile);

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
    for (int ihx=0; ihx<(*nhyp); ihx++) cout << "Will run hyp "<<(*shyp)[ihx]<<" code "<<(*hyp)[ihx]<<" with "<<(*nPointsHyp)[ihx]<<" iterations"<<endl;
  }

  return;
}

void ConfigParser::ReadIntegrationRange(){
  if (valVerbosity>=1) cout << "Integration will use JetTFfracmin="<< valJetTFfracmin<<" JetTFfracmax="<< valJetTFfracmax <<" NeutMaxE="<< valNeutMaxE <<endl;
  return;
}

void ConfigParser::ReadJetChoice(){
  if (valVerbosity>=1) cout << "In 2j categories, choose 2 jets with option "<< valJetChoice<< endl;
  return;
}

void ConfigParser::ReadOptim(){

  if (valVerbosity>=1) cout << "Optimizing phase space with option: "<< valOptim <<endl;
  if (valVerbosity>=1) cout << "Optimizing phase space with option: TopHad "<< valOptimTopHad<<", TopLep "<< valOptimTopLep<< ", Higgs "<< valOptimHiggs<< ", Woffshell "<< valOptimW<<endl;

}

void ConfigParser::SetCSVThreshold(double value)
{
  std::cout << "Setting b-tagging WP to: " << value << '\n';
  valCsvThresh = value;
}

void ConfigParser::SetTransferFunction(string TFpath){

  valTFfile = TFpath;
  if (valVerbosity>=1) cout << "Using transfer function: "<<valTFfile<<endl;

  return;
}

void ConfigParser::SetMadgraphDir(string MGpath){

  valMadgraphDir = MGpath;
  if (valVerbosity>=1) cout << "Using Madgraph path: "<<valMadgraphDir<<endl;

  return;
}

void ConfigParser::SubstituteEnv(std::string & path)
{
  std::vector<std::string> path_split;
  boost::split(path_split, path, [](char c) -> bool { return c == '/'; });
  std::vector<std::string> path_new_vec;
  for(const std::string & path_part: path_split)
  {
    if(path_part.empty())
    {
      continue;
    }
    if(path_part[0] == '$')
    {
      const char * env = std::getenv(path_part.substr(1).data());
      if(! env)
      {
        assert(0);
      }
      path_new_vec.push_back(std::string(env));
    }
    else
    {
      path_new_vec.push_back(path_part);
    }
  }
  const std::string path_new = boost::algorithm::join(path_new_vec, "/");
  if(path != path_new)
  {
    std::cout << "Changing path from '" << path << "' to '" << path_new << "'\n";
    path = path_new;
  }
  return;
}


#endif
