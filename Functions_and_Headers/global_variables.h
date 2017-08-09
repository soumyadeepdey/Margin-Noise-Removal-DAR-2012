

//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Program Name : marginal_noise_removal.cpp
// 
// Project :  		DRD
// Author : 		Soumyadeep Dey
// Creation Date : 	FEB 14  -2012.  Rights Reserved
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*

#ifndef globalvariables_H
#define globalvariables_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

#include "structures.h"

using namespace std;

/*------------------------------------------------------- Global variables----------------------------------------------------------------------*/


is *(*tempstructuredimage);

nocc *component;
nocc *originalcomponent;


Mat src, src_gray, binary_dst, output_image, erode_dst, dilate_dst, color_para, para_fill,dst;





int row,col,maximum;
int *img;
int *colorimage;
int *binary_image;
int *(*imgg);
int *(*imgg1);
int ncc;
int tncc;// total number of connected component
int ncco;//number of connected component in original image

int npar;//number of paragraph total
int number_para=0;// total number of paragraphs or text regions


nocc *newparagraph;



int pgfrmxmin,pgfrmxmax,pgfrmymin,pgfrmymax; // declaring page frame co-ordinate as global veriable



//parameters
int old_doc=0;// variable to told doc old or new   // put 0 if not old(if you dont want to dilate the binary image before finding connected component)
int graphicsthreashold=2500; // IT IS THE THRESHOLD SET BASED ON 300 DPI SCAN TO SEPARATE GRAPHICS BASED ON CC SIZE AFTER STUDING ON 50 IMAGES
int threshold_value = 0;
int threshold_type = 0;;
int const maximum_value = 255;
int const maximum_type = 4;
int const maximum_BINARY_value = 255;
int const blockSize=101;




/*-----------------------------------------------------------------------------------------------------------------*/

#endif