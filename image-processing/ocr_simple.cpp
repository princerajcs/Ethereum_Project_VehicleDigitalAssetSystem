#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include<regex>
#include<sys/types.h>
#include<dirent.h>

using namespace std;
using namespace cv;

int isDirectoryEmpty(char *dirname) {

  int n = 0;
  struct dirent *d;
  DIR *dir = opendir(dirname);
  if (dir == NULL) //Not a directory or doesn't exist
  return 1;
  while ((d = readdir(dir)) != NULL) {
  if(++n > 2)
  break;
  }

  closedir(dir);
  if (n <= 2) //Directory Empty
  return 1;
  else
  return 0;

} 
int main(int argc, char* argv[])
{
    string outText;
    char *dirname = "/home/Input/";
   // isDirectoryEmpty(dirname);	
 //   string imPath = "/home/Input/image.jpg";
  	string imPath = argv[1];
  Mat gray;

    // Create Tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
     
    // Initialize tesseract to use English (eng) and the LSTM OCR engine. 
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
 
    // Set Page segmentation mode to PSM_AUTO (3)
    ocr->SetPageSegMode(tesseract::PSM_AUTO);
    
    // Open input image using OpenCV
    Mat im = cv::imread(imPath, IMREAD_COLOR);
    
    cv::resize(im,im,cv::Size(),0.50,0.50,CV_INTER_CUBIC);
//     cv::resize(im, im, fx=1.2, fy=1.2, interpolation=cv::INTER_CUBIC)
    // Set image data
    cv::cvtColor(im,gray, CV_BGR2GRAY);
    ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
 
    // Run Tesseract OCR on image
    outText = string(ocr->GetUTF8Text());
 
    string sname = outText.substr(outText.find("Name")+5);
    auto name = sname.substr(0,sname.find('\n'));
    cout<<"&&&&&&&The name is &&&&&&&&&&&"<<name<<endl;
//    cout << "this is output "<< outText << "till here"<< endl; // Destroy used object and release memory ocr-
    std::smatch m;
    std::regex e ("(DL).(No).");
    std::regex_search ( outText, m, e );
    auto sstr = outText.substr(m.position(1));//outText.find('\n'))<<endl;
    auto dlno = sstr.substr(0,sstr.find('\n'));
    cout<<"!!!!The Lis number is !!!"<<dlno<<endl;

    fstream fp;
    cout<<"File creation invoked!!!\n";
    fp.open("/home/campus/image-proc/pgms/Output/DL.txt");
    fp << dlno;
    cout<<"File writing done!!!\n";
    fp.close();    

    
    return EXIT_SUCCESS;
}



//g++ -O3 -std=c++11 ocr_simple.cpp `pkg-config --cflags --libs tesseract opencv`-o ocr_simple
