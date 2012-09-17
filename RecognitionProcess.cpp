
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
#include "StdAfx.h"
#include "RecognitionProcess.h"
#include "FileManipulating.h"
#include <iostream>

#define FRAME_HT 40
#define FRAME_WD 8

using namespace std;



RecognitionProcess::RecognitionProcess(void)
{
}

RecognitionProcess::RecognitionProcess(System::String* path,int **imgArray)
{
	this->imageArr = imgArray;
	
	this->imWidth = 0;
	this->imHeight = 0;

	this->scriptFilePath = this->scriptFilePath->Concat(path ,"\\htk\\recognizer\\script.txt");
	this->HMMListFilePath = this->HMMListFilePath->Concat(path ,"\\htk\\files\\hmmlist.txt");
	this->exeFileDir = this->exeFileDir->Concat(path ,"\\htk\\executables\\");
	this->mmfFilePath = this->mmfFilePath->Concat(path ,"\\htk\\files\\nepaliOCR.mmf");
	this->mlfFilePath = this->mlfFilePath->Concat(path ,"\\htk\\files\\labeled.mlf");
	this->dictFilePath = this->dictFilePath->Concat(path ,"\\htk\\files\\def\\dict.txt");
	this->wordNetFilePath = this->wordNetFilePath->Concat(path ,"\\htk\\files\\def\\net.slf");
	this->recognitionTempFileDir = this->recognitionTempFileDir->Concat(path ,"\\htk\\recognizer\\");
	//this->aakarsList = new System::Collections::ArrayList();
	//this->rassoEEkarList = new System::Collections::ArrayList();

}

void RecognitionProcess::ImageBoundarySet(int left_x, int right_x,int top_y, int bottom_y)
{
	 
	this->leftX=left_x;
	this->rightX=right_x;
	this->topY=top_y;
	this->bottomY=bottom_y;
}

System::Collections::SortedList* RecognitionProcess::LoadModelTranscriptions(System::String* dbFilePath)
{
	// load the model transcription database
	 System::IO::StreamReader* sr = System::IO::StreamReader::Null;
	 slModel = new System ::Collections::SortedList();


	 System::String* key;
	 System::String* tempStr;
	 int count=0;
	 bool modelName = true;
	 try
	 {
		sr = new System::IO::StreamReader(dbFilePath);
		while(sr->Peek()>=0)
		{
			
			tempStr=sr->ReadLine();
			if(tempStr->Equals("*"))
			{
				count = 0;
				slModel->Add(key,alModelTrans);
				
				
			}
			else
			{
				if(count==0)
				{
					key = tempStr;
					alModelTrans = new System::Collections::ArrayList();
					count++;
				}
				else
				{
					alModelTrans->Add(tempStr);
	//PostProcessing Details Here
					 //ArrayList aakarList contains list of model names
	//				if(tempStr->Equals("093E")){
	//					this->aakarsList->Add(key);
	////PostProcessing Details here
					//	
					//}
					//if(tempStr->Equals("093F")){
					//	this->rassoEEkarList->Add(key);
					//}
				}
			}
			//if(tempStr->Equals("093E")){
			//	System::Windows::Forms::MessageBox::Show("Found",key->ToString());
			//}
		} //End while
		sr->Close();
		 
		//while(aaKarList->GetEnumerator()->MoveNext()){
		//	  
		//	myaaKarListCounter++;
		//}
		return slModel;
	 }
	 catch(System::Exception* ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Load the Model DataBase!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
		exit(0);
	}
}


void RecognitionProcess::SetImageBoundary(int left_x, int right_x,int top_y, int bottom_y)
{
	this->leftX = left_x;
	this->rightX = right_x;
	this->topY = top_y;
	this->bottomY = bottom_y;

	//Setting the training image boundary...	
	//this->ImageBoundarySet(this->leftX,this->rightX,this->topY,this->bottomY);
}


void RecognitionProcess::PrepareWordData(System::String* wordFeatureFile)
{
	FileManipulating* fm = new FileManipulating();
	fm->PrepareData(wordFeatureFile, this->imageArr, this->leftX, this->rightX, this->topY, this->bottomY);
}

System::Collections::ArrayList* RecognitionProcess::RecognizeByHTK()
{
	FileManipulating* fm = new FileManipulating();
	fm->RecognizeByHMM(this->recognitionTempFileDir,this->exeFileDir,this->mmfFilePath,this->mlfFilePath,this->wordNetFilePath,this->dictFilePath,this->HMMListFilePath, this->scriptFilePath); 
	
	System::Collections::ArrayList* al = fm->FetchOutputModels(this->mlfFilePath);
	

	return al;
}