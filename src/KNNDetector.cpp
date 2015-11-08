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
}

void KNNDetector::classify(const vector<float> &vec, int &c, float &score) {
  int n = 5;
  c = -1;
  vector<int> ind(n);
  vector<float> dis(n);
  fill(dis.begin(), dis.end(), FLT_MAX);
  auto len = feavec.rows;
  for (int i = 0; i < len; i++) {
    auto temp = norm(feavec.row(i), vec);
    int j = n;
    while (j > 0 && temp < dis[j - 1]) {
      if (j < n) {
        dis[j] = dis[j - 1];
      }
      j--;
    }
    if (j < n) {
      dis[j] = temp;
      ind[j] = i;
    }
  }

  map<int, int> count = map<int, int>();
  if (dis[0] < 12) {
    /*
     * the 12 value is based on experience with human hog data.
     * which is 160x96 or 128x96, and ~1500 after PCA, it doesn't
     * mater very much because of the KNN, but it is still better
     * to use a dim related  threshold instead
     */
    for (auto i = 0; i < n; i++) {
      int nind = ind[i];
      int nclu = clus[nind];
      count[nclu]++;
      // cout<<nind<<"\t:\t"<<nclu<<"\t:\t"<<dis[i]<<endl;
    }
    int max = 0;
    int maxi = -1;
    for (const auto &p : count) {
      if (p.second > max) {
        max = p.second;
        maxi = p.first;
      }
    }
    if (max > 1) {
      c = maxi;
      for (auto i = 0; i < n; i++) {
        if (clus[ind[i]] == maxi) {
          score = dis[i];
          break;
        }
      }
    } else {
      c = -1;
    }
  } else {
    c = -1;
  }
}
