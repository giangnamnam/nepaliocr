
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

public __gc class RecognitionProcess
{
public:
	// attributes
	int leftX;		// left x coordinate of the image
	int rightX;	    // right x coordinate of the image
	int topY;		// top y coordinate of the image
	int bottomY;	// bottom y coordinate of the image
	int imWidth;	// width of the image
	int imHeight;	// height of the image

	int **imageArr;	// Image pixel array

	System::String* scriptFilePath;	// path of the script file	
	System::String* HMMListFilePath;// path of the HMM List File
	System::String* exeFileDir;		// path of the Executables File
	System::String* mmfFilePath;	// path of the Master Model File(MMF)
	System::String* mlfFilePath;	// path of the Master Labeled File(MLF)
	System::String*	dictFilePath;   // path of the Dictionary File
	System::String*	wordNetFilePath;// path of the Word Network File
	System::String*	recognitionTempFileDir;	// path of the temporary file directory

	System ::Collections::SortedList* slModel;		// list to store the model transcription database
	System ::Collections::ArrayList* alModelTrans;
 
	//System::Collections::ArrayList *aakarsList;
	//System::Collections::ArrayList *rassoEEkarList;
	//System::Collections::ArrayList *aaKarList;
	System::String* dbFilePath;

	// constructors
	RecognitionProcess(void);
	RecognitionProcess(System::String* path, int **imgArray);
	//RecognitionProcess(System::String* path,int **imgArray, int left_x, int right_x,int top_y, int bottom_y);

	/*Methods*/
	// loading the transcription of the trained models
	System::Collections::SortedList* LoadModelTranscriptions(System::String* dbFilePath);
	 

	// setting the image boundary
	void ImageBoundarySet(int left_x, int right_x,int top_y, int bottom_y);

	// setting the word image boundary
	void SetImageBoundary(int left_x, int right_x,int top_y, int bottom_y);

	// reading the word image information and write the features into a file in binary format
	void PrepareWordData(System::String* wordFeatureFile);

	// recognize the image words using the HTK Toolkit
	System::Collections::ArrayList* RecognizeByHTK();
};
