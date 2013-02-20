//
//  FeaturePartitioner.cpp
//  HumanPoseDetector
//
//  Created by Lichao Chen on 2/19/13.
//  Copyright (c) 2013 Lichao Chen. All rights reserved.
//

#include "FeaturePartitioner.h"
void FeaturePartitioner::exportPatches(vector<int> category, string srcdir, string desdir){
    
    if (*srcdir.rbegin()!='/'){
        srcdir = srcdir+"/";
    }
    if (*desdir.rbegin()!='/'){
        desdir = desdir+"/";
    }
    
    
    for(int i=0;i<category.size();i++){
        string fn = to_string(i+1)+".jpg";
        Mat im = imread(srcdir+fn);
        imwrite(desdir+to_string(category[i])+"/"+fn, im);
    }
}
void FeaturePartitioner::kmean(Mat& feavec, vector<int>& category, int k){
    cout<<"Start k-mean clustering"<<endl;
    kmeans(feavec, k, category, TermCriteria(CV_TERMCRIT_ITER, 30, 0), 5, KMEANS_PP_CENTERS);
    cout<<"Done k-mean clustering"<<endl;
}