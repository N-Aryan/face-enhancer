#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace cv;
using namespace std;


double calcSharpness(const Mat& img) {
    Mat gray, lap;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Laplacian(gray, lap, CV_64F);
    Scalar mu, sigma;
    meanStdDev(lap, mu, sigma);
    return sigma.val[0] * sigma.val[0];
}

int main() {
    vector<String> files;
    glob("images/*.jpg", files);        
    if (files.empty()) {
        cout << "No images found in /images folder!" << endl;
        return -1;
    }

    for (auto &path : files) {
        Mat img = imread(path);
        if (img.empty()) {
            cerr << "Could not read: " << path << endl;
            continue;
        }


        Mat kernel = (Mat_<float>(3,3) <<
                       0, -1,  0,
                      -1,  5, -1,
                       0, -1,  0);
        Mat sharpened;
        filter2D(img, sharpened, img.depth(), kernel);


        Mat lab;
        cvtColor(sharpened, lab, COLOR_BGR2Lab);
        vector<Mat> lab_planes(3);
        split(lab, lab_planes);
        Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8,8));
        clahe->apply(lab_planes[0], lab_planes[0]);
        merge(lab_planes, lab);
        cvtColor(lab, sharpened, COLOR_Lab2BGR);


        Mat denoised;
        fastNlMeansDenoisingColored(sharpened, denoised, 5, 5, 7, 21);


        double beforeSharp = calcSharpness(img);
        double afterSharp  = calcSharpness(denoised);
        double gain = ((afterSharp - beforeSharp) / max(beforeSharp, 1.0)) * 100.0;


        size_t pos = path.find_last_of('/');
        string name = path.substr(pos + 1);
        imwrite("output/enhanced_" + name, denoised);


        Mat combined(img.rows, img.cols*2, img.type());
        img.copyTo(combined(Rect(0, 0, img.cols, img.rows)));
        denoised.copyTo(combined(Rect(img.cols, 0, img.cols, img.rows)));
        imwrite("output/comparison_" + name, combined);


        cout << fixed << setprecision(1);
        cout << "Enhanced: " << name
             << " | Sharpness Before: " << beforeSharp
             << " | After: " << afterSharp
             << " | Gain: " << gain << "%" << endl;
    }

    cout << "All images processed successfully!\n"
         << "Results saved in /output folder." << endl;

    return 0;
}
