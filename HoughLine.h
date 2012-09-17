
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
 * Author : Rajesh Pandey ::  nepaliocr@gmail.com
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
#pragma once

using namespace System::Collections;
using namespace System;

public __gc class HoughLine
{
public:
	int Count; 	// Count of points in the line.
	int Index; 	// Index in Matrix.
	double Alpha; 
	// The line is represented as all x,y that solve y*cos(alpha)-x*sin(alpha)=d
	double d;

	/*int Count;
	int Index;
	double Alpha;
	double d;*/
};



/*
//houghline algorithm :: as folows
public HoughLine(double angle,
                 int radius,
                 int accumulator,
                 int width,
                 int height);

*/
