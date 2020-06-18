#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
int main(int argc, char* argv[])
{
    string outText;
    string imPath = argv[1];
 
    // Create Tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
     
    // Initialize tesseract to use English (eng) and the LSTM OCR engine. 
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
 
    // Set Page segmentation mode to PSM_AUTO (3)
    ocr->SetPageSegMode(tesseract::PSM_AUTO);
    

    // Open input image using OpenCV
    Mat im = cv::imread(imPath, IMREAD_COLOR);
    
    cv::resize(im,im,cv::Size(),0.50,0.50);
     
    // Set image data
    ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
 
    // Run Tesseract OCR on image
    outText = string(ocr->GetUTF8Text());
/*
    std::ofstream out("out.txt");
    out << outText;
    out.close();
ifstream in_stream; 
    string filein("out");
    string search_name("Name");
    string search_number("DL.No");              

    in_stream.open (filein.c_str(), ios::in | ios::binary); //Opens the file
*/
//     std::size_t pos = outText.find("Name");
  //   string name =  outText.substr(pos);
 
  //  cout << "name is " << name <<endl; 
    // print recognized text
string sname = outText.substr(outText.find("Name")+5);
//cout<<"@@@@@@@@@@@@"<<sname<<endl;    
auto name = sname.substr(0,sname.find(' '));
cout<<"&&&&&&&&&&&&&&&&&&"<<name<<endl;
//cout << "this is output "<< outText << "till here"<< endl; // Destroy used object and release memory ocr->End();
string sdlno = outText.substr(outText.find("DL.No")+5);
auto dlno = sdlno.substr(0,sdlno.find('\n'));
cout<<"!!!!!!!"<<dlno<<endl;

    return EXIT_SUCCESS;
}



//g++ -O3 -std=c++11 ocr_simple.cpp `pkg-config --cflags --libs tesseract opencv`-o ocr_simple
