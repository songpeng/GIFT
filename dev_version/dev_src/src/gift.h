// The head file for the method of gift.

// GIFT is used to predicte the interactions between compounds substructures and
// protein domains from the known drug-protein interactions.
// See the details:
// http://bioinformatics.oxfordjournals.org/content/31/15/2523.abstract

// Author: Songpeng Zu
// Email: zusongpeng@gmail.com
// Date: 2016-03-06

#ifndef __GIFT_H__
#define __GIFT_H__

// C/C++ system library
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
// Boost library
#include<boost/thread/thread.hpp>

namespace gift {
  // gift information.
  const std::string author{"Songpeng Zu"};
  const std::string email{"zusongpeng@gmail.com"};
  const std::string version{"gift-2.0"};
  const std::string updateTime{"2016-03-06"};

  // read and write matrix, temp use vector<vector> as container.
  template <typename T> int readMatrix(const std::ifstream&,
                                       std::vector<std::vector<T> >&);
  template <typename T> int writeMatrix(const std::ifstream&,
                                        std::vector<std::vector<T> >&);
  // help function and outRecord function.
  int helpGift();
  int outRecord(parameters&, EM&);

  // classes
  class parameters {
  public:
    // initialization: default and from init file.
    parameters ();
    parameters (std::ifstream&) {};

    int setDrugNum(unsigned int);
    int setSubNum(unsigned int);
    int setProteinNum(unsigned int);
    int setDomainNum(unsigned int);

    // public members
    bool loglikelyRecord;
    double fn;
    double fp;
    unsigned int thread;
    unsigned int iterationNum;
    unsigned int drugNum;
    unsigned int subNum;
    unsigned int domainNum;
    unsigned int proteinNum;
    std::string task;
    std::string chemfpRec;
    std::string proteinfpRec;
    std::string CPIsRec;
    std::string outFilePrefixCPIs;
    std::string outFilePrefixTrain;
  }; // end of class parameters
  class EM {
  public:
    // Inition with parameters
    EM(parameters&);
    // Default Destruction
    ~EM();
    // Core of EM.
    int EStep();
    int MStep();
    int initEM();
    int loglikely();
    int trainEM();
    int predictEM();
    int setLoglikely(double);
    int outTrain(std::ofstream&);
    int outPredict(std::ofstream&);
  private:
    double fn;
    double fp;
    unsigned int thread;
    unsigned int iterationNum;
    unsigned int drugNum;
    unsigned int subNum;
    unsigned int domainNum;
    unsigned int proteinNum;
    std::string task;
    // or use static with pointer.
    std::vector<std::vector<unsigned int> > * drug2sub;
    std::vector<std::vector<unsigned int> > * proein2sub;
    std::vector<std::vector<unsigned int> > * drug2protein;
    std::vector<std::vector<double > > * drugSub2proteinSub;
    std::vector<double> * loglikely;
  };// end of class EM

} // end of namepsace gift

#endif // end of GIFT_H