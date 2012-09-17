
/**
 *   OCR
 * Programmed in Visual C++ 2003 
 * Microsoft Windows XP 
 * Professional 
 * Version 2002 
 * Service Pack 3  
 * Intel[R] 
 * Pentium 4 CPU  2.80 GHZ 
 * Intel Core I3 2.2 GHZ 4 CPUs
 *
 *
 * Requirements:
 *  
 * win2k or later\n
 * .NET FrameWork 1.1 or later 
 *
 * Version 1.0
 * first version
 *
 * Date 07-01-2008
 *
 ** Credits : 
  * Authors : 
  * Rajesh Pandey ::  nepaliocr@gmail.com
  * Sanjeev Maharjan
 * 
 *
 *
 * license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 *  
 *
 *  
 *
 */

#include "Separate.h"
#include "Line.h"
#include "ThresholedValue.h"
#include "rgbConvert.h"


#pragma once


using namespace System::Drawing;
using namespace System::Collections;
using namespace System;

public __gc class Resegment
{
private:
		int SizeThresHold;     //Threshold Size value which separates the touching characters from others
		Bitmap* img;			//source image
		Bitmap* cropImage;		//Unit Image 
		int ImHeight;			
		int ImWidth;
		int *WStore;			// Array to store the width of all the units in the image
		int totalunits;			// total number of the connected units in the image
		int *TouchingCharacterIndex;
		bool BinaryDone;

		bool Resegmentation_Complete;	
		bool ImageLoaded;
		bool SeparateDone;
		bool **BinArray;
		int numberOfLines;
		Line *Lines;
		Graphics *g;
		int flevel;
		int *Horizontal;
		int **HeadBottom; //Array with the information of headline position and bottomline position

public:
	Resegment(Bitmap* im,bool BinaryDone,bool ImageLoaded,bool SeparateDone, bool **BinArray,int numberOfLines, Line *Lines, Graphics *g,int totalUnits, int SizeThreshold,int flevel,int **headbottom);
	void WidthStore(); //Stores the width values to the array
	void TotalUnitCount(); //Calculates total unit count
	int ThresholdSize();	// Calculates and Returns Threshold Image
	void Do_Segmentation();	// Performs the resegmentation
	void Crop_Image(int lineno,int wordno,int charno); //crops the character unit image from given position
	int MultiFactorialAnalysis(int Headline_Pos,int Bottom_Pos);	// Performs the Multifactorial Analysis
	int minimum(int *num,int width); // Returns the minimum number from the given array
	int maximum(float *num,int width); //Returns the Largest Float value
	int maximum(int *num,int width); //Returns the largst integer value
	void sortWidth(); //Sort the width in ascending order
	int Truncate(int val); // Rounding off the float value
	void adjustUnits(int lineno,int wordno,int charno); // Adjust the boundaries after identifying the cut column
	void getPixelInRows(int height,int width,bool **bArray);
	int headLinePosition(int height,int width);
	int bottomLinePosition(int height,int width, int maxIndex,bool **BinaryArray);
//	void PrepareTouchingCharIndex();

};



	
