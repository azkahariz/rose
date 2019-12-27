#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Inisialisasi jumlah feature yang ingin didteksi
const int MAX_FEATURES = 2000;

// Inisilaisasi persentase fitur yang ingin diambil
const float GOOD_MATCH_PERCENT = 0.05f;

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

int main()
{

    // Menyalakan kamera, 0 = Camera laptop, 1 = Camera USB
    cap.open(1);
    // Cek apakah kamera terbuka
    if(!cap.isOpened()){
        cerr << "ERROR! Unable to open camera \n";
        return -1;
    }

    // Membaca gambar referensi
    string refFilename("/home/azkahariz/QTProject/Rose/gambar/drawing2.jpg");
    cout << "Reading reference image : " << refFilename << endl;
    Mat imReference = imread(refFilename);
    // Mengkonversi gambar menjadi hitam putih
    cvtColor(imReference, imReference, CV_BGR2GRAY);
    // Membuat tampilan
    namedWindow("matches.jpg", WINDOW_KEEPRATIO);

    // for(;;) proses pencuplikan gambar
    for(;;)
    {
        // Mencuplik gambar
        cap >> src;
        // Mengkonversi gambar tercuplik ke hitam putih
        cvtColor(src, src, CV_BGR2GRAY);
        // Mendeteksi fitur pada gambar video menggunakan ORB
        orb -> detectAndCompute(src, Mat(), keypoints1, descriptors1);
        // Mendeteksi fitur pada gambar referensi menggunakan ORB
        orb -> detectAndCompute(imReference, Mat(), keypoints2, descriptors2);
        // Mencari titik korespondensi
        matcher->match(descriptors1, descriptors2, matches, Mat());
        // Melakukan sortir titik korespondensi dari yang terbaik
        // ke yang terburuk
        std::sort(matches.begin(), matches.end());
        // Mengeleminasi titik korespondensi sesuai dengan persentase
        // yang diinginkan
        const int numGoodMatches = matches.size() * GOOD_MATCH_PERCENT;
        matches.erase(matches.begin()+numGoodMatches, matches.end());
        // Menggambar dan menampilkan titik korespondensi
        drawMatches(src, keypoints1, imReference, keypoints2, matches, imMatches);
        imshow("matches.jpg", imMatches);
        // Menampilkan jumlah titik korespondensi
        cout << "Match: " << matches.size() << endl;
        // Jeda
        waitKey(33);
    }

}
