
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

/*
*	This class is used for Running an external PostProcesor 
*	which is used for modifying the output of the OCR
*/


#pragma once

public __gc class externalPostProcessor
{
public:
	externalPostProcessor(System::String *applicationPath,System::String *PostProcessorApplicationFileName);
public: 
	void tryNewProcesor(void);
	 
public: System::String* getText();
private:
	 
	System::String *inputFileName, *outputFileName;
	 
	System::String *outputString;
	
	 
	 
};
