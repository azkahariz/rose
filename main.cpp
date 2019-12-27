#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int MAX_FEATURES = 2000;
const float GOOD_MATCH_PERCENT = 0.01f;

int main()
{
    cv::VideoCapture cap;
    // Menyalakan kamera, 0 = Camera laptop, 1 = Camera PS3
    cap.open(1);
    // Cek apakah kamera terbuka
    if(!cap.isOpened()){
        cerr << "ERROR! Unable to open camera \n";
        return -1;
    }

    // Read reference image
    string refFilename("/home/azkahariz/QTProject/ObjectDetection/gambar/drawing2.jpg");
    cout << "Reading reference image : " << refFilename << endl;
    Mat imReference = imread(refFilename);
    cvtColor(imReference, imReference, CV_BGR2GRAY);

    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2, im;
    Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);
    std::vector<DMatch> matches;
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    namedWindow("matches.jpg", WINDOW_KEEPRATIO);
    for(;;)
    {

        string imFilename("scanned-form.jpg");
        cap >> im;
        cvtColor(im, im, CV_BGR2GRAY);
        orb -> detectAndCompute(im, Mat(), keypoints1, descriptors1);
        orb -> detectAndCompute(imReference, Mat(), keypoints2, descriptors2);
        matcher->match(descriptors1, descriptors2, matches, Mat());
        std::sort(matches.begin(), matches.end());

        const int numGoodMatches = matches.size() * GOOD_MATCH_PERCENT;
        matches.erase(matches.begin()+numGoodMatches, matches.end());

        Mat imMatches;
        drawMatches(im, keypoints1, imReference, keypoints2, matches, imMatches);

        imshow("matches.jpg", imMatches);
        cout << "Match: " << matches.size() << endl;
        waitKey(1000);
    }

}
