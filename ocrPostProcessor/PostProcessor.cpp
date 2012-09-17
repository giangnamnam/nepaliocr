#include ".\postprocessor.h"
#using <mscorlib.dll>
using namespace System;

PostProcessor::PostProcessor(System::String *tempStr)
{
	//this->myTempStr = tempStr;
	int i;

	this->processStr = this->processStr->Trim();

	//if ((pos = this->processStr->IndexOf("FILEVERSION")) < 0)
	//	  continue;
	//   pos += "FILEVERSION".Length + 1;

	//System::String  tempInfo = this->processStr->Substring(pos)
	// string[] tempInfo = line.Substring(pos).Split(" .,".ToCharArray());


	System::Collections::ArrayList *ch = new System::Collections::ArrayList();
//	ch = this->processStr->ToCharArray();
	//this->processStr->ToCharArray
	
	int len = this->processStr->Length;

}

PostProcessor::~PostProcessor(void)
{
	 

}
System::String *PostProcessor::TextPostProcessor(){
	return this->processStr;
}
bool PostProcessor::IsDependentVowel(unsigned short Vowel)
		 {
			  
			 const unsigned short aakar = 2494;
			 const unsigned short rossoikar = 2495;
			 const unsigned short dirgikar = 2496;
			 const unsigned short rossoUkar = 2497;
			 const unsigned short dirgUkar = 2498;
			 const unsigned short rrikar = 2499;
			 const unsigned short ekar = 2503;
			 const unsigned short oikar = 2504;
			 const unsigned short o_kar = 2507;
			 const unsigned short ou_kar = 2508;

			 
			 switch(Vowel)
			 {
			 case aakar:
			 case rossoikar:
			 case dirgikar:
			 case rossoUkar:
			 case dirgUkar:
			 case rrikar:
			 case ekar:
			 case oikar:
			 case o_kar:
			 case ou_kar:
			 return true;
			 break;
			 };

			 return false;
		 }