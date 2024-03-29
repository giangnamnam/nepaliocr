#include "HoughLine.h"

#pragma once

using namespace System::Collections;
using namespace System;
using namespace System::IO;

public __gc class Deskew
{



public:
	//The Bitmap
 	static Bitmap* cBmp;
	//The range of angles to search for lines
	//static double cAlphaStart= -20;
	static double cAlphaStart= -20;
	static double cAlphaStep= 0.2;
	static int cSteps= 40 * 5;
	//Precalculation of sin and cos.
	static double *cSinA;
	static double *cCosA;
	//Range of d
	static double cDMin;
	static double cDStep= 1;
	static int cDCount;

	//Count of points that fit in a line.
	static int *cHMatrix;


	Deskew(Bitmap* im);

	double GetSkewAngle();
	void Calc();
	void Init();
	double GetAlpha(int Index);
	bool IsBlack(int x,int y);
	void Calc(int x,int y);
	double CalcDIndex(double d);
	HoughLine* GetTop(int count)[];

};

//## Deskew::Deskew(Bitmap* im) ##
Deskew::Deskew(Bitmap* im)
{
	cBmp=im;
}

//##### double Deskew::GetSkewAngle() ####
//Calculate the skew angle of the image cBmp.
double Deskew::GetSkewAngle()
{
	HoughLine *h1[];		//creating a pointer
	int i;
	h1=new HoughLine* [20];	//creating new array of class HoughLine, array of size 20 
 	double sum=0;			//initializing sum
	int count=0;			//initializing count

	Calc();					//calculate
	//Hough Transformation
	
	h1=this->GetTop(20);
	//Top 20 of the detected lines in the image.

	//Average angle of the lines
	for (i = 0; i <= 19; i++) 
		{
			
			sum+=h1[i]->Alpha;
			
			//if(h1[i]->Alpha==-20){ System::Windows::Forms::MessageBox::Show("Alpha is 20","What happened");}
			
			count+=1;
		}
		if(sum/count==-20){
			System::Windows::Forms::MessageBox::Show("The image must be already deskewed. \n\n\nIf the image is still skewed then it might be out of the scope of the deskew algorithm used", "Image is already Deskewed");
			return 0;
		}
		else{
			return sum/count;
		}
	
}


//######### void Deskew::Calc() ###########
void Deskew::Calc()
{
	int x;
	int y;
	double bMin=(cBmp->Height) / 4;
	double bMax=cBmp->Height * 3 / 4;

	int hMin=(int)bMin;
	int hMax=(int)bMax;

	//bMin = 1/4th of ImageHeight
	//bMax = 3/4th of ImageHeight
//	System::Windows::Forms::MessageBox::Show(hMin.ToString()/*fLevel.ToString()*/,"bMin");
//	System::Windows::Forms::MessageBox::Show(hMax.ToString()/*fLevel.ToString()*/,"bMax");					
	Init();

	//y runs from 1/4th of image to 3/4th of image
	for(y=hMin;y<=hMax;y++)
		{
			//x runs from 1 to (width of image-2)
			for(x=1;x<=(cBmp->Width)-2;x++)
				{
				// Only lower edges are considered.
				if (IsBlack(x, y))
				{
					if (!IsBlack(x, y + 1))
					{
						Calc(x, y);
					}
				}
			}
		}
}
//################################## Deskew :: Init() ###############
void Deskew::Init()
{
	int i;
	double angle;
	// Precalculation of sin and cos.
		//  ReDimStatement
		// ReDimStatement
	cSinA=new double [cSteps-1];
	cCosA=new double [cSteps-1];


	for(i=0;i<=cSteps-1;i++)
		{
			angle=(GetAlpha(i)) * (System::Math::PI) / 180.0;
			cSinA[i]=System::Math::Sin(angle);		//find sine angle
			cCosA[i]=System::Math::Cos(angle);		//find cosine angle
		}
	
	cDMin= -(cBmp->Width);
	double cDCount0=2*(cBmp->Width + cBmp->Height)/ cDStep;

	cDCount=(int)cDCount0;
	cHMatrix=new int [cDCount * cSteps];

	for(int i=0;i<=(cDCount*cSteps)-1;i++)
	{
		cHMatrix[i]=0;
	}
}


//##################### Deskew :: GetAlpha #############
double Deskew::GetAlpha(int Index)
{
	return cAlphaStart + (((double) Index) * cAlphaStep) ;
}

bool Deskew::IsBlack(int x,int y)
{
	Color c;
	double luminance;
	int pixel;
	int red;
	int green;
	int blue;

	System::Drawing::Color clr = cBmp->GetPixel(x,y);
	pixel = clr.ToArgb();				

	

	red = (pixel >> 16) & 0xff;
	green = (pixel >>  8) & 0xff;
	blue = (pixel      ) & 0xff;
	
	luminance = (0.299 * red) + (0.587 * green) + (0.114 * blue);
	return luminance < 140;
}


//################# Deskew :: Calc(int x, int y) ##################
// Calculate all lines through the point (x,y).
void Deskew::Calc(int x,int y)		//parameters image pixels(x, and y) coordinates
{
	int alpha;
	double d;
	int dIndex,Index;			
	



	for(alpha=0;alpha<=cSteps-1;alpha++)
	{
		
		d=(y * cCosA[alpha])- (x * cSinA[alpha]); //x Cos(alpha) + y Sin(alpha) = P
												  //P = x Cos(alpha) + y Sin(alpha)
												  //this turns out to be :
													// d = y Cos(alpha) + x Sin(alpha)
													// d = y cCos(alpha) - x cSin(alpha)
		dIndex=CalcDIndex(d);
		Index=(dIndex*cSteps)+alpha;
		 
		
		
		
		cHMatrix[Index]+=1;
		

	}

}

//########### double Deskew::CalcDIndex(double d) #######
double Deskew::CalcDIndex(double d)
{
	return System::Convert::ToInt32(d - cDMin);
}

//######## HoughLine* Deskew::GetTop(int count)[] ###
//Calculate the Count lines in the image with most points.
HoughLine* Deskew::GetTop(int count)[]
{
	HoughLine* h1[]=new HoughLine*[20]; //declaration 
	int i;
	int j;
	HoughLine* tmp;				//temporary houghline datatype
	int AlphaIndex;				//temp 
	int dIndex;					//temp 
			
	// ERROR: Not supported in C#: ReDimStatement
	// :::: Some vb codes are left unimplemented here August 18, 2007 ::::::::: 

	for(i=0;i<=(count -1);i++)   //initialize the value of houghline, initially to zero 
	{							//Continue until it increases upto count
		h1[i]=new HoughLine();
	}


	for(i=0;i<count;i++)
	{
		h1[i]->Count=0;			//initialize each components of houghline to zero
		h1[i]->Index=0;			//initialize
		h1[i]->Alpha=0;			//initialiae
		h1[i]->d=0;				//initialiae
	}

				//temp
	
	int hlLength=(int)cDCount*cSteps;
	
	for(int i=0;i<=hlLength-1;i++)
		{
					
			if(cHMatrix[i]>(h1[count-1]->Count))
				{
					h1[count-1]->Count=cHMatrix[i];
                	h1[count-1]->Index=i;
					j=count-1;
					while(j>0 && (h1[j]->Count > h1[j-1]->Count))
						{
							tmp=h1[j];
							h1[j]=h1[j-1];
							h1[j-1]=tmp;
							j -= 1;  // means j--;
						}
				}
		}

	
	//StreamWriter *sw=new StreamWriter("trial.txt");

	for(int i=0;i<=count-1;i++)
		{
			dIndex=(h1[i]->Index) / cSteps;
			AlphaIndex=h1[i]->Index - dIndex * cSteps;
			h1[i]->Alpha=GetAlpha(AlphaIndex);
			h1[i]->d=dIndex + cDMin;
		}
	
	

	return h1;

}