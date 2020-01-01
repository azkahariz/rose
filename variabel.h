#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <math.h>
#ifndef VARIABEL
#define VARIABEL



using namespace std;
using namespace cv;

// Background Substraction
Ptr<BackgroundSubtractor> pBackSub;
Mat frame, fgMask;

// Inisialisasi jumlah feature yang ingin didteksi
const int MAX_FEATURES = 2000;

// Inisilaisasi persentase fitur yang ingin diambil
const float GOOD_MATCH_PERCENT = 0.01f;

// Berfungsi untuk mendeteksi keypoint pada gambar referensi dan video real-time
std::vector<KeyPoint> keypoints1, keypoints2;

// Deskriptor pada gambar referensi dan video real-time
Mat descriptors1, descriptors2;

// Berfungsi untuk mencuplik frame pada video real-time
Mat src;

// Membuat variabel deteksi fitur
Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);

// Membuat varibael titik korespondensi
Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
std::vector<DMatch> matches;

// Variabel cuplik video
VideoCapture cap;

// Variabel untuk menampilkan titik korespondensi
Mat imMatches;

// Varibale untuk gambar referensi
Mat imReference;

// Registered image will be resotred in imReg.
// The estimated homography will be stored in h.
Mat imReg, h;

// Untuk mencari homography
std::vector<Point2f> points1, points2;

Mat img;
// Koordinat
std::vector<Point2d> titik, titik2;

Mat imRegGray;
stringstream ss;
string JarakText, degreeText;
int jarakX, jarakY, radius;
double jarak, degree;
vector<Vec3f> circlesTarget, circlesBomb;


#endif // VARIABEL
