#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat image;
Point point1, point2;
int  dragA, select_flagA;
bool callbackA = false;
RNG rng(12345);
std::vector<Rect> boundRect;
int thresh = 40;
Mat src_gray;
Mat drawing;
std::vector<Rect> partes;
int qtds[15];
String strpartes[15] = {"C","B","A","F", "E","D","I", "H", "G", "L","K", "J", "O", "N", "M"};
void DetectarObjetos(int, void *){
    Mat canny_output;
    std::vector< std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;

    cvtColor(image, src_gray, CV_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    Canny(src_gray, canny_output, thresh, thresh * 3, 3);
    findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    std:: vector< std::vector<Point> > contours_poly(contours.size());


    boundRect.clear();

    for (unsigned int i = 0; i < contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        boundRect.push_back(boundingRect(Mat(contours_poly[i])));

    }

     drawing = Mat::zeros(canny_output.size(), CV_8UC3);

    for (unsigned int i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
    }



}
void ContarEmPartes(){
    memset (qtds,0,15);
    for (vector<Rect>::iterator it = boundRect.begin(); it!=boundRect.end(); ++it) {
        for(int i=0; i < partes.size(); i++) {
            if((it.base()->tl().x >= partes.at(i).tl().x  &&  it.base()->br().x <= partes.at(i).br().x)
                    &&
                    (it.base()->tl().y >= partes.at(i).tl().y  &&  it.base()->br().y <= partes.at(i).br().y)
                    ){
                qtds[i]++;
            }
        }

    }


    for(int i=0; i < 15; i++) {
        std::cout<<strpartes[i]<<": " << qtds[i] <<std::endl;
    }


}
static void mouseHandler(int event, int x, int y, int flags, void *param) {

    if (event == CV_EVENT_LBUTTONDOWN && !dragA && !select_flagA) {

        point1 = cv::Point(x, y);
        dragA = 1;
    }

    if (event == CV_EVENT_MOUSEMOVE && dragA && !select_flagA) {

        point2 = cv::Point(x, y);
        rectangle(image, point1, point2, CV_RGB(255, 0, 0), 2, 5, 0);
        imshow("Display window", image);
    }

    if (event == CV_EVENT_LBUTTONUP && dragA && !select_flagA) {
        point2 = cv::Point(x, y);
        rectangle(image, point1, point2, CV_RGB(255, 0, 0), 2, 5, 0);
        dragA = 0;
        callbackA = true;
        imshow("Display window", image);
        std::cout << point1 << " "<< point2 << std::endl;
        if (point1.y > point2.y || point1.x > point2.x) {
            printf("Horientação errada para detecção de cor.");

        }
    }
}
int main( int argc, char** argv )
{
        cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;



    image = imread("partes2.png", CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    DetectarObjetos(0, 0);



    int altura = 128;
    int largura = 89;
    point1.x = 90;
    point1.y = 58;

    for(int i = 0; i < 5; i++){
        point1.y = 58;
        point2.y = 58+altura;
        point2.x=point1.x+largura;
        for(int l = 0; l < 3; l++){
            rectangle(drawing, point1, point2, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 5, 0);
             partes.push_back(Rect(point1, point2));
             point2.y+=altura;
             point1.y+=altura;
        }
        point1.x+=largura;
    }

    ContarEmPartes();
    imshow("Contornos", drawing);
  //  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    //imshow("Display window", image);
     waitKey(0);
    std::cout << partes.size() <<std::endl;


//      while(true) {
//    imshow("Display window", image);
//
//cv::setMouseCallback("Display window", mouseHandler, 0);
//        if(waitKey(0))
//           break;
//}

    return 0;
}