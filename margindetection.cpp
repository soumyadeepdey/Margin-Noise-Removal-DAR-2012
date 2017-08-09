
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*
// Program Name : marginal_noise_removal.cpp
// 
// Project :  		DRD
// Author : 		Soumyadeep Dey
// Creation Date : 	JUNE 10  -2012.  Rights Reserved
//~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*~^~*


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;


#include "Functions_and_Headers/structures.h"
#include "Functions_and_Headers/global_variables.h"


#include "Functions_and_Headers/binarization.h"
#include "Functions_and_Headers/morphologi.h"
#include "Functions_and_Headers/smoothing.h"
#include "Functions_and_Headers/con_comp.h"
#include "Functions_and_Headers/makedirectory.h"
#include "Functions_and_Headers/noise_remove_and_page-frame.h"


#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

// #include "Functions_and_Headers/xml_Lib_src/xmlParser.h"
// #include "Functions_and_Headers/xml_Lib_src/schemaParser.cpp"
// #include "Functions_and_Headers/xml_Lib_src/xmlParser.cpp"
// #include "Functions_and_Headers/xml.h"
// #include "Functions_and_Headers/xml.cpp"
// 
// IITKGP_XML_IO::XML_IO IITKGP;

#include "folder.h"


/*---------------------------------------------------------------------------MAIN FUNCTION------------------------------------------------------------------------*/



int main (int argc, char *r[])
{
	int i,j;
	//makedir("step");  // Folders are created to store some data if required
	//makedir("temp"); // temporary folders

	char c;
	char *name;
	FILE *fp;
	char *input_image_name;
	
	//input_image_name=IITKGP.readXML(r[1]);
	
	input_image_name=r[1];
	char *dirname;
	dirname = (char *)malloc(2001*sizeof(char));
	name = (char *)malloc(2001*sizeof(char));
	name = IITkgp_functions::input_image_name_cut(r[1]);
	strcpy(dirname,name);
	char *temp;
	temp=(char *)malloc(2001*sizeof(char));
	temp = ".pgm";
	char *newname;
	newname = (char *)malloc(2001*sizeof(char));
	strcpy(newname,name);
	strcat(newname,temp);
	
	name = (char *)malloc(2001*sizeof(char));
	
	name = IITkgp_functions::CreateNameIntoFolder(dirname,"LabelAllInOne.png");

	src=imread(name,1);
	
	char *name1;
	name1 = (char *)malloc(2001*sizeof(char));
	
	name1 = IITkgp_functions::CreateNameIntoFolder(dirname,newname);
	
	IITkgp_functions::makedir("DAR12");

	row=src.rows;
	col=src.cols;
	maximum=255;
	
	cvtColor( src, src_gray, CV_RGB2GRAY ); // converting color to gray scale image
	
	imwrite(name1,src_gray);
	
	img=(int *)malloc(row*col*sizeof(int));  // SOURCE IMAGE GRAY SCALE

	for(i=0;i<row*col;i++)
	{
		img[i]=src_gray.data[i];
	}

	
	// BINARIZATION	
	binary_image=(int *)malloc(row*col*sizeof(int));

	binary_image=binarization();


/* ------------------------------------------------------------- NOISE REMOVAL ------------------------------------------*/

	// dilation if old document

	int *dilatedimage;
	dilatedimage=(int*)malloc(row*col*sizeof(int));

	if(old_doc==1)
	{
		
		dilatedimage=dilation(binary_image);
	}

	
	
	// FINDING CONNECTED COMPONENT on the IMAGE

	int *(*im);
	im=(int **)malloc(row * sizeof(int *));
	for(i=0;i<row;i++)
	{
		im[i]=(int *)malloc(col * sizeof(int));
	}
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if(old_doc==1)
				im[i][j]=dilatedimage[i*col+j]; //for old document connection lost finding cc on dilated image
			else
				im[i][j]=binary_image[i*col+j]; // for document where connection not lost finding cc on binary image
		}
	}



	connectedcomponent(im);	

	noise_removal();

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



	output_image=imread("actual_outputimage.pgm",0);
	
	system("rm actual_outputimage.pgm");
	//system("rm resultimage.png");
	//system ("rm -r step "); // removing folders and its content
	//system ("rm -r temp ");  // removing folders and its content
	
	char *outname;
	outname = (char *)malloc(2001*sizeof(char));
	
	outname = IITkgp_functions::CreateNameIntoFolder("DAR12_new",r[1]);

	imwrite(outname,output_image);
	
	
	
	/**********************************UNPAPER*********************************/
	
	
	IITkgp_functions::makedir("Unpaper");
	name=(char *)malloc(2001*sizeof(char));
	name = IITkgp_functions::CreateNameIntoFolder("Unpaper",newname);
	
	char *systemcall,*vari;
	temp=(char *)malloc(2001*sizeof(char));
	vari=(char *)malloc(2001*sizeof(char));
	vari="unpaper -l single --no-mask-center --no-deskew ";
	strcpy(temp,vari);
	char *temp1;
	temp1=(char *)malloc(2001*sizeof(char));
	strcpy(temp1,temp);
	strcat(temp1,name1);
	temp==(char *)malloc(2001*sizeof(char));
	strcpy(temp,temp1);
	vari=(char *)malloc(2001*sizeof(char));
	vari=" ";
	strcat(temp,vari);
	systemcall=(char *)malloc(2001*sizeof(char));
	strcpy(systemcall,temp);
	strcat(systemcall,name);
	
	system(systemcall);
	
	
	/*
	printf("PAGE-FRAME XMIN=%d\tXMAX=%d\tYMIN=%d\tYMAX=%d\n",pgfrmxmin,pgfrmxmax,pgfrmymin,pgfrmymax);
	char *xmlchild;
	xmlchild = "TextBlock";
	IITKGP.writemyxml(r[1],r[2],xmlchild,input_image_name,r[3],"NULL", "NULL",pgfrmxmin,pgfrmymin,pgfrmxmax,pgfrmymax);
	*/
	printf("\n");
	
	free(binary_image);
	free(dilatedimage);
	free(im);
	return 0;

}





/*-----------------------------------------------------------------------END OF MAIN----------------------------------------------------------------*/
