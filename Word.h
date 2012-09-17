
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
 * This code has no bugs, just undocumented features!
 * 
 *  
 *
 *  
 *
 */
#pragma once
#include "Unit.h"

class Word
{
//private: int WordNo;
private: int TotalUnit;
private: int StartColumn;
private: int EndColumn;

public:

	Unit *Units;

	Word(void)
	{
	}

	///sc -> starting column number of line
	///ec -> ending column number of line
	void set( int sc, int ec )
	{
		this->StartColumn = sc;
		this->EndColumn = ec;
	}
	///Ut -> number of units in this word
	void setUnit(int Ut)
	{
		this->TotalUnit = Ut;
		Units = new Unit[Ut];
	}
	int getStartColumn()
	{
		return this->StartColumn;
	}
	///
	int getEndColumn()
	{
		return this->EndColumn;
	}

	int getTotalUnit()
	{
		return this->TotalUnit;
	}
};
