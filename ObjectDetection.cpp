#include "variabel.h"

void OpenCamera(){
    // Menyalakan kamera, 0 = Camera laptop, 1 = Camera USB
    cap.open(1);
    // Cek apakah kamera terbuka
    if(!cap.isOpened()){
        cerr << "ERROR! Unable to open camera \n";
    }
}

void ReadReference()
{
    // Membaca gambar referensi
    string refFilename("/home/azkahariz/QTProject/Rose/gambar/drawing2.jpg");
    cout << "Reading reference image : " << refFilename << endl;
    imReference = imread(refFilename);
    // Mengkonversi gambar menjadi hitam putih
    cvtColor(imReference, imReference, CV_BGR2GRAY);
}

void onMouse(int event, int x, int y, int flags, void* userdata)
{

    if  ( event == EVENT_LBUTTONDOWN )
    {
        titik.push_back(Point2d(x,y));
        circle(imReference, Point(x,y), 5, 256, 1);
    }
}

void onMouse2(int event, int x, int y, int flags, void* userdata)
{

    if  ( event == EVENT_LBUTTONDOWN )
    {
        titik2.push_back(Point2d(x,y));
        circle(src, Point(x,y), 5, 256, 1);
    }
}

void MatchingImage()
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
}

void tampilkanMatching()
{
    MatchingImage();
    // Menggambar dan menampilkan titik korespondensi
    drawMatches(src, keypoints1, imReference, keypoints2, matches, imMatches);
    imshow("matches.jpg", imMatches);

}

void imageAlignment()
{
    if(matches.size()>5)
    {
        for(size_t i = 0; i < matches.size(); i++){
            points1.push_back( keypoints1[ matches[i].queryIdx ].pt );
            points2.push_back( keypoints2[ matches[i].trainIdx ].pt );
        }
        // Find homography
        h = findHomography( points1, points2, RANSAC );

        // Use homography to warp image
        warpPerspective(src, imReg, h, imReference.size());
        cout << h << endl;
        // Tampilkan aligned image

        imshow("aligned image",imReg);
    }
}

void pilihTitikReference()
{
    while(titik.size() < 5)
    {
        setMouseCallback("Template", onMouse, NULL);
        imshow("Template", imReference);
        waitKey(33);
    }
    titik.erase(titik.end());

}

void pilihTitikKamera()
{
    cap >> src;
    cvtColor(src, src, CV_BGR2GRAY);
    while(titik2.size() < 5)
    {
        setMouseCallback("Kamera", onMouse2, NULL);
        imshow("Kamera",src);
        waitKey(33);
    }
    titik2.erase(titik2.end());
}

void BackgroundSubtraction()
{
    GaussianBlur(imReg,frame,Size(15,15),0);
    pBackSub->apply(frame,fgMask);
}

int main()
{

    pBackSub = createBackgroundSubtractorMOG2();
    OpenCamera();
    ReadReference();
    namedWindow("Template", WINDOW_KEEPRATIO);
    pilihTitikReference();
    namedWindow("Kamera", WINDOW_KEEPRATIO);
    pilihTitikKamera();
    cout << "Titik template: " << titik << endl;
    cout << "Titik kamera: "  << titik2 << endl;
    h = findHomography(titik2,titik);
    cout << h << endl;
    warpPerspective(src, imReg, h, imReference.size());
    namedWindow("aligned image", WINDOW_KEEPRATIO);
    imshow("aligned image",imReg);
    waitKey(0);

    namedWindow("Process",WINDOW_KEEPRATIO);
    namedWindow("FG Mask",WINDOW_KEEPRATIO);
    // for(;;) proses pencuplikan gambar
    for(;;)
    {

        cap >> src;
        warpPerspective(src, imReg, h, imReference.size());
        BackgroundSubtraction();
        imshow("Process",imReg);
        imshow("FG Mask", fgMask);
        waitKey(33);
    }
    return 0;

}
