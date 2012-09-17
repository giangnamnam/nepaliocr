
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
 * Date 11-01-2008
 *
 ** Credits : 
 * Author : Rajesh Pandey ::  nepaliocr@gmail.com
 *
 *
 * license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code in this particular file MAY HAVE SOME BUGS! The Author bears no warranty for this.
 * 
 *  
 *
 *  
 *
 */
#ifndef DESKEW_H
#define DESKEW_H

#include "HoughLine.h"

#pragma once

using namespace System::Collections;
using namespace System;
using namespace System::IO;
//using namespace System::Drawing::Bitmap;

 

 
/*
	Deskew.h

	This is the header file with declarations 
	This class is used for Deskewing Image.
	Thanks to GMSE Deskew 
	(Original Program in Visual Basic)
	Modified for Nepali OCR in Visual C++ By Rajesh Pandey

	This algorithm uses the popular line drawing algorithm
	y = mx+c 
	i.e. Angle = x Cos (alpha) + y Sin (alpha) 

	Browse the CPP file for more Details

*/


public __gc class Deskew
{



public:
	//The Bitmap
	static System::Drawing::Bitmap *cBmp;
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
	 

	Deskew(System::Drawing::Bitmap * im);

	double GetSkewAngle();
	void Calc();
	void Init();
	double GetAlpha(int Index);
	bool IsBlack(int x,int y);
	void Calc(int x,int y);
	double CalcDIndex(double d);
	HoughLine* GetTop(int count)[];



};

#endif