#include <opencv2/opencv.hpp>
#include "ImageCropper.h"

using namespace std;
ImageCropper::ImageCropper(void)
{
	patch_r = 160;
	patch_c = 96;
	stride = (patch_c+patch_r)/4;
}


ImageCropper::~ImageCropper(void)
{
}

void ImageCropper::setSize(int r,int c)
{
	patch_r = r;
	patch_c = c;
}

void ImageCropper::setUp(Mat img){
	pyr = vector<Mat>(10);
	all_candidates = vector<Rect>();
	all_candidate_mats=vector<Mat>();
	vector<double> level_scale;

	double scale = 1.;
	double scale0 = 1.2;
	int levels = 0;

	for (levels = 0; levels < 40; levels++)
	{
		level_scale.push_back(scale);
		if (cvRound(img.cols/scale) < patch_c ||
			cvRound(img.rows/scale) < patch_r || scale0 <= 1)
			break;
		scale *= scale0;
	}

	levels = std::max(levels, 1);
	level_scale.resize(levels);


	size_t i;
	for (i = 0; i < level_scale.size(); i++)
	{
		scale = level_scale[i];
		Size sz(cvRound(img.cols / scale), cvRound(img.rows / scale));
		Mat smaller_img;

		if (sz == img.size())
			smaller_img = img;
		else
		{
			resize(img,smaller_img, sz);
		}
		pyr.push_back(smaller_img);
		Size scaled_win_size(cvRound(patch_c * scale), cvRound(patch_r * scale));
		for(int k=0;k<smaller_img.rows -patch_r+1;k+=stride)
			for(int j=0; j<smaller_img.cols - patch_c+1;j+=stride){
				all_candidates.push_back(Rect(Point2d(j,k) * scale, scaled_win_size));
				all_candidate_mats.push_back(smaller_img(Range(k,k+patch_r),Range(j,j+patch_c)));
			}
	}
	pyr.resize(i);

}

