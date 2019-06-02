#pragma once

#include "FeatureLoader.h"
#include "PatchClassDetector.h"
#include "opencv2/ml.hpp"
#include <fstream>
#include <memory>

using namespace cv;
using namespace cv::ml;

class KNNDetector : public PatchClassDetector {
public:
  KNNDetector(void) {}
  KNNDetector(string vecfname, string clusfname);
  KNNDetector(const Mat &featurevec, vector<int> &clusvec)
      : clus(clusvec), feavec(featurevec) {}
  ~KNNDetector(void) {}
  virtual void classify(const vector<float> &vec, int &c,
                        float &score) override;
  void load(string fsfn, string clusfn) override; // load feature and indice
                                                  // list
protected:
  vector<int> clus;                               // cluster tag
  Mat feavec;                                     // feature index, hold memory
  Ptr<TrainData> trainingData;                    // A wrapper of above
  Ptr<KNearest> kclassifier = KNearest::create(); // knn classifier
};
