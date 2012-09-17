
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
#include<iostream>


/*
*	File Manipulating 
*
*	Functions: 
*
*---------------------------- 
*----------------------------
*	TRAINING
*----------------------------
*---------------------------- 
*
*-----------------------------
*	CreatePrototypeFile 
*		Creates Prototype, for training process
*----------------------------
*	CreateHMMFile 
*		Creates HMM file , used for Training process.
*----------------------------
*	AddModelDefToMasterModelFile
*		Creates Master Model File (MMF) file, used for Training Process
*----------------------------
*	AddModelNameToHMMListFile
*		Appends the HMM List 
*----------------------------
*
*---------------------------- 
*----------------------------
*	RECOGNITION
*---------------------------- 
*----------------------------
*
*	BuildWordNetwork
*		Builds Word Network : Used for Recognition 
*----------------------------
*	PrepareData
*		Prepare Data for Recognition
*----------------------------
*	RecognizeByHMM
*		Recognition Using HTK executables (RUN the HVITE.exe)
*----------------------------
*	FetchOutputModels
*		Fetch Output Model Names. This Output Model Names will ultimately provide the outputs
*----------------------------
*	ApplyDCT
*		Applying Discrete Cosine Transform
*----------------------------
*	Fdct
*		DCT
*----------------------------
*/

using namespace std;
public __gc class FileManipulating
{
public:
	// attributes
	float **dctArr; // dct array
	int numOfFrame;

	// constructor
	FileManipulating(void);
	
	/* Methods */

	// For Training
	System::String* GetModelName(System::String* filePath);
	void CreatePrototypeFile(System::String* Fromfile, System::String* Tofile, System::String* modelName);
	void CreateHMMFile(System::String* exeFileDir,System::String* outputHmmDir,System::String* prototypeFile,System::String* trainFile);
	void AddModelDefToMasterModelFile(System::String* mmfFilePath, System::String* fromHmmFile);
	void AddModelNameToHMMListFile(System::String* hmmListFile, System::String* hmmNameFile, System::String* modelName);
	void BuildWordNetwork(System::String* gramFile, System::String* dictFile, System::String* transFile, System::String* wdnetFileDir, System::String* execpath, System::String* modelName);

	// For both Training and Recognition
	void PrepareData(System::String* dataFileName, int **imageArr, int leftX, int rightX, int topY, int bottomY);

	// For Recognition
	void RecognizeByHMM(System::String* recDir, System::String* execFile, System::String* mmfFile, System::String* mlfFile, System::String* wdNetFile, System::String* dictFile, System::String* hmmListFile, System::String* scriptFile);
	System::Collections::ArrayList* FetchOutputModels(System::String* mlfFilePath);

	// apply DCT
	void ApplyDCT();
	float Fdct(int u, int v);
};
