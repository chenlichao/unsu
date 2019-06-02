#include "KNNDetector.h"

KNNDetector::KNNDetector(string vecfn, string clusfn) { load(vecfn, clusfn); }

void KNNDetector::load(string vecfn, string clusfn) {
  // Load vector matrix
  auto fl = FeatureLoader();
  feavec = fl.loadTab(vecfn);
  int in_count = feavec.rows;

  // Load cluster index
  ifstream fin(clusfn);
  clus = vector<int>(in_count);
  for (int i = 0; i < in_count; i++) {
    fin >> clus[i];
  }
  fin.close();

  trainingData = TrainData::create(feavec, ml::ROW_SAMPLE, clus);

  // We are using classifier mode
  kclassifier->setIsClassifier(1);
  kclassifier->setAlgorithmType(KNearest::BRUTE_FORCE);
  kclassifier->setDefaultK(11);

  kclassifier->train(trainingData);

  // Just checking the settings
  cout << "Training data: " << endl
       << "getNSamples\t" << trainingData->getNSamples()
       << endl // Number of training samples
       << endl;

  cout << "Classifier :" << endl
       << "kclassifier->getDefaultK(): " << kclassifier->getDefaultK() << endl
       << "kclassifier->getIsClassifier()   : "
       << kclassifier->getIsClassifier() << endl
       << "kclassifier->getAlgorithmType(): " << kclassifier->getAlgorithmType()
       << endl
       << endl;
}

void KNNDetector::classify(const vector<float> &vec, int &c, float &score) {
  c = kclassifier->findNearest(vec, kclassifier->getDefaultK(), noArray());
  // TODO: score can be obtained from avg distances of neighbors of selected
  // category.
}
