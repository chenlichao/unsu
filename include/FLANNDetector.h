#pragma once
#include "PatchDetector.h"
#include <fstream>
#include <memory>

using namespace cv;
using namespace flann;

class FLANNDetector : public PatchDetector {
public:
  FLANNDetector(void);
  FLANNDetector(string vecfname, string indfname);
  FLANNDetector(const Mat &featureVec, vector<int> &indvec);

  ~FLANNDetector(void){};
  virtual void detect(const vector<float> &vec, int &c, float &score,
                      bool &accepted) override;

  void save(string fsfn, string indfn); // save feature and indice list and kNN
                                        // index to FileStorage;
  void load(string fsfn, string indfn)
      override; // load feature and indice list and kNN index from FileStorage
  void loadText(string vecfn, string clusfn); // load feature nad indice list
                                              // from text file, and init index
  void loadYAML(string fsfn, string indfn); // load feature nad indice list from
                                            // text file, and init index

private:
  vector<int> clus;         // cluster tag
  shared_ptr<Index> feaind; // index for knn search
  Mat feavec;               // feature index, hold memory
  int vlen;                 // hard coded vector length, not good..
  void init();
};
