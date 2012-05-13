#include "Line.h"
#include "TrainingProcess.h"

#pragma once

	using namespace System;
	using namespace System::Data;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Drawing::Imaging;




namespace OCR
{
	/// <summary> 
	/// Summary for TrainingForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class TrainingForm : public System::Windows::Forms::Form
	{
	public: 
		TrainingForm(void)
		{
			this->applicationPath=Application::StartupPath->ToString();
			
			int len = this->applicationPath->Length -1;			
			if(this->applicationPath->Substring(len)->Equals("\\"))
			{
				this->applicationPath = this->applicationPath->Substring(0,len);				
			}

			// getting the character database path
			//System::Windows::Forms::MessageBox::Show(this->applicationPath,"Path of characterDB path");

			this->characterDBPath=this->characterDBPath->Concat(this->applicationPath ,"\\htk\\DataBaseFile\\characters.txt");	
			//System::Windows::Forms::MessageBox::Show(this->characterDBPath,"Path of characterDB path");
			
			this->modelTrainDBPath = this->modelTrainDBPath->Concat(this->applicationPath , "\\htk\\DataBaseFile\\modelTrainDataBase.txt");
			// getting the path of the word to be tranied for which the recognition output is shown
			this->wordToRec = this->wordToRec->Concat(this->applicationPath ,"\\htk\\files\\trainfile.txt");

			this->alForCharacters = new System::Collections::ArrayList();

			InitializeComponent();
			//this->applicationPath = Application::StartupPath->ToString();
			// for the directory, path appear an extra '/'
			// here we are removing that '/'
			bool enableTrainingOnTextChanged = false;
		}
        
	protected: 
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

	
	private: 
		bool** BinArray;
		int **ImageArray;
		Line* LineInfo;
		int lineCount;
		Bitmap* cropImage;
		static int lineno=0;
		static int wordno=0;
		static int charno=0;
		private: int x1,x2,y1,y2;
		private: String* applicationPath;
				 String* characterDBPath;
				 String* modelTrainDBPath;
				 String* modelName;
    
    // for recognition
	private: String* wordToRec;
	private: System::Collections::ArrayList* alRec;


		private: System::Collections::SortedList* slForCharacters;
		private: System::Collections::ArrayList* alForCharacters;
				 System::Collections::IEnumerator* charEnumerator;


		private: System::Windows::Forms::TextBox *  combineChar;
	private: System::Windows::Forms::StatusBar *  statusBar1;
	private: System::Windows::Forms::Label *  lblOutput;
	private: System::Windows::Forms::MainMenu *  trainMenu;
	private: System::Windows::Forms::MenuItem *  mnuTrainer;



	private: System::Windows::Forms::MenuItem *  menuItem4;
	private: System::Windows::Forms::MenuItem *  mnuAdd;
	private: System::Windows::Forms::MenuItem *  mnuTrain;
	private: System::Windows::Forms::MenuItem *  mnuExit;
	private: System::Windows::Forms::MenuItem *  mnuNext;
	private: System::Windows::Forms::MenuItem *  mnuPrevious;



	private: System::Windows::Forms::Button *  addChar;
			bool enableTrainingOnTextChanged;
		


	public: 
		
		void defineVar(int** ImgArray,bool** BArray,Line* Lines,int numberOfLines)
			{
				this->ImageArray=ImgArray;
				this->BinArray=BArray;
				this->LineInfo=Lines;
				this->lineCount=numberOfLines;
				this->display(this->lineno,this->wordno,this->charno);
				this->LoadComboBoxFromFile();
			}


		void display(int lineno,int wordno,int charno)
		{
			x1=this->LineInfo[lineno].Words[wordno].Units[charno].getStartColumn();
			x2=this->LineInfo[lineno].Words[wordno].Units[charno].getEndColumn();
			y1=this->LineInfo[lineno].getStartRow();
			y2=this->LineInfo[lineno].getEndRow();

			int xsize=x2-x1+1;
			int ysize=y2-y1+1;
			
			//xsize=400;
			//ysize=400;

			this->cropImage=new Bitmap(xsize,ysize,Imaging::PixelFormat::Format24bppRgb);
			
			for(int i=y1;i<=y2;i++)
			{
				for(int j=x1;j<=x2;j++)
				{
					if(this->BinArray[i][j])
					{
						this->cropImage->SetPixel(j-x1,i-y1,Color::White);
					}
					else
					{
						this->cropImage->SetPixel(j-x1,i-y1,Color::Black);
					}
			    }
			}
			this->pictureBox1->Image=cropImage;
		}

		public: System::Collections::SortedList* getSortedList()
				 {
					 return this->slForCharacters;
				 }

		private: void LoadComboBoxFromFile()
		 {
			System::IO::StreamReader* sr = System::IO::StreamReader::Null;
			System::String* tempStr;
			System::String* charStr;
			System::String* unicodeStr;
			int index;

			try
			{
				slForCharacters = new System::Collections::SortedList();
				// read the characters and store
				sr = new System::IO::StreamReader(this->characterDBPath);
				tempStr = sr->ReadLine();
				while (tempStr->Length!=0)
				{
					index = tempStr->IndexOf(" ");
					charStr = tempStr->Substring(0,index);
					unicodeStr = tempStr->Substring(index+1);
					if(!slForCharacters->ContainsKey(charStr)){
						slForCharacters->Add(charStr,unicodeStr);
						this->characterBox->Items->Add(charStr);
					}
					tempStr = sr->ReadLine();
				}
				sr->Close();
			}
			catch(System::Exception* ex)
			{
				System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Can't load the Combo box!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
				exit(0);
			}
		 }

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::PictureBox *  pictureBox1;






	private: System::Windows::Forms::Button *  nextButton;
	private: System::Windows::Forms::Button *  prevButton;
	private: System::Windows::Forms::ComboBox *  characterBox;
	private: System::Windows::Forms::Button *  trainButton;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container* components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(OCR::TrainingForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->nextButton = new System::Windows::Forms::Button();
			this->prevButton = new System::Windows::Forms::Button();
			this->characterBox = new System::Windows::Forms::ComboBox();
			this->trainButton = new System::Windows::Forms::Button();
			this->combineChar = new System::Windows::Forms::TextBox();
			this->addChar = new System::Windows::Forms::Button();
			this->statusBar1 = new System::Windows::Forms::StatusBar();
			this->lblOutput = new System::Windows::Forms::Label();
			this->trainMenu = new System::Windows::Forms::MainMenu();
			this->mnuTrainer = new System::Windows::Forms::MenuItem();
			this->mnuAdd = new System::Windows::Forms::MenuItem();
			this->mnuTrain = new System::Windows::Forms::MenuItem();
			this->mnuExit = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->mnuNext = new System::Windows::Forms::MenuItem();
			this->mnuPrevious = new System::Windows::Forms::MenuItem();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(8, 8);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(128, 128);
			this->panel1->TabIndex = 0;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(16, 8);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(104, 112);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// nextButton
			// 
			this->nextButton->Location = System::Drawing::Point(296, 40);
			this->nextButton->Name = S"nextButton";
			this->nextButton->Size = System::Drawing::Size(56, 40);
			this->nextButton->TabIndex = 7;
			this->nextButton->Text = S"NEXT>> (Ctrl N)";
			this->nextButton->Click += new System::EventHandler(this, nextButton_Click);
			// 
			// prevButton
			// 
			this->prevButton->Location = System::Drawing::Point(200, 40);
			this->prevButton->Name = S"prevButton";
			this->prevButton->Size = System::Drawing::Size(72, 40);
			this->prevButton->TabIndex = 8;
			this->prevButton->Text = S"<<Previous (Ctrl P)";
			this->prevButton->Click += new System::EventHandler(this, prevButton_Click);
			// 
			// characterBox
			// 
			this->characterBox->Location = System::Drawing::Point(16, 168);
			this->characterBox->Name = S"characterBox";
			this->characterBox->Size = System::Drawing::Size(121, 21);
			this->characterBox->TabIndex = 9;
			// 
			// trainButton
			// 
			this->trainButton->Location = System::Drawing::Point(304, 200);
			this->trainButton->Name = S"trainButton";
			this->trainButton->Size = System::Drawing::Size(56, 40);
			this->trainButton->TabIndex = 10;
			this->trainButton->Text = S"Train (Ctrl S)";
			this->trainButton->Click += new System::EventHandler(this, trainButton_Click);
			// 
			// combineChar
			// 
			this->combineChar->Location = System::Drawing::Point(168, 168);
			this->combineChar->Name = S"combineChar";
			this->combineChar->TabIndex = 11;
			this->combineChar->Text = S"";
			this->combineChar->TextChanged += new System::EventHandler(this, combineChar_TextChanged);
			// 
			// addChar
			// 
			this->addChar->Location = System::Drawing::Point(304, 160);
			this->addChar->Name = S"addChar";
			this->addChar->Size = System::Drawing::Size(56, 34);
			this->addChar->TabIndex = 12;
			this->addChar->Text = S"Add (CtrlA)";
			this->addChar->Click += new System::EventHandler(this, addChar_Click);
			// 
			// statusBar1
			// 
			this->statusBar1->Location = System::Drawing::Point(0, 244);
			this->statusBar1->Name = S"statusBar1";
			this->statusBar1->Size = System::Drawing::Size(400, 22);
			this->statusBar1->TabIndex = 14;
			// 
			// lblOutput
			// 
			this->lblOutput->Location = System::Drawing::Point(200, 96);
			this->lblOutput->Name = S"lblOutput";
			this->lblOutput->Size = System::Drawing::Size(48, 24);
			this->lblOutput->TabIndex = 15;
			// 
			// trainMenu
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__1[0] = this->mnuTrainer;
			__mcTemp__1[1] = this->menuItem4;
			this->trainMenu->MenuItems->AddRange(__mcTemp__1);
			// 
			// mnuTrainer
			// 
			this->mnuTrainer->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__2[0] = this->mnuAdd;
			__mcTemp__2[1] = this->mnuTrain;
			__mcTemp__2[2] = this->mnuExit;
			this->mnuTrainer->MenuItems->AddRange(__mcTemp__2);
			this->mnuTrainer->Text = S"Trainer";
			// 
			// mnuAdd
			// 
			this->mnuAdd->Index = 0;
			this->mnuAdd->Shortcut = System::Windows::Forms::Shortcut::CtrlA;
			this->mnuAdd->Text = S"&Add";
			this->mnuAdd->Click += new System::EventHandler(this, addChar_Click);
			// 
			// mnuTrain
			// 
			this->mnuTrain->Index = 1;
			this->mnuTrain->Shortcut = System::Windows::Forms::Shortcut::CtrlS;
			this->mnuTrain->Text = S"&Train";
			this->mnuTrain->Click += new System::EventHandler(this, trainButton_Click);
			// 
			// mnuExit
			// 
			this->mnuExit->Index = 2;
			this->mnuExit->Shortcut = System::Windows::Forms::Shortcut::CtrlW;
			this->mnuExit->Text = S"&Exit";
			this->mnuExit->Click += new System::EventHandler(this, mnuExit_Click);
			// 
			// menuItem4
			// 
			this->menuItem4->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__3[0] = this->mnuNext;
			__mcTemp__3[1] = this->mnuPrevious;
			this->menuItem4->MenuItems->AddRange(__mcTemp__3);
			this->menuItem4->Text = S"Scroll";
			// 
			// mnuNext
			// 
			this->mnuNext->Index = 0;
			this->mnuNext->Shortcut = System::Windows::Forms::Shortcut::CtrlN;
			this->mnuNext->Text = S"&Next";
			this->mnuNext->Click += new System::EventHandler(this, nextButton_Click);
			// 
			// mnuPrevious
			// 
			this->mnuPrevious->Index = 1;
			this->mnuPrevious->Shortcut = System::Windows::Forms::Shortcut::CtrlP;
			this->mnuPrevious->Text = S"&Previous";
			this->mnuPrevious->Click += new System::EventHandler(this, prevButton_Click);
			// 
			// TrainingForm
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(400, 266);
			this->Controls->Add(this->lblOutput);
			this->Controls->Add(this->statusBar1);
			this->Controls->Add(this->addChar);
			this->Controls->Add(this->combineChar);
			this->Controls->Add(this->trainButton);
			this->Controls->Add(this->characterBox);
			this->Controls->Add(this->prevButton);
			this->Controls->Add(this->nextButton);
			this->Controls->Add(this->panel1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Menu = this->trainMenu;
			this->Name = S"TrainingForm";
			this->Text = S"TrainingForm";
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}	

		

	
	private: System::Void nextButton_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 if(charno<this->LineInfo[lineno].Words[wordno].getTotalUnit()-1)
				 {
					this->charno++;
				 }
				 else
				 {
					 //this->charno=0;
					 if(wordno< this->LineInfo[lineno].getTotalWord()-1)
					 {
						 this->wordno++;
						 this->charno=0;
					 }


					 else
					 {
						 this->wordno=0;
						 this->charno=0;
						 if(lineno<this->lineCount-1)
						 {
							 this->lineno++;
						 }
						 else
						 {
							 this->lineno=0;
							 this->wordno=0;
							 this->charno=0;
						 }
					 }
				 }
				 this->display(this->lineno,this->wordno,this->charno);
				 this->Update();
			 }

private: System::Void prevButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(charno > 0) //this->LineInfo[lineno].Words[wordno].getTotalUnit()-1)
				 {
					this->charno--;
				 }
				 else
				 {
					 //this->charno=0;
					 if(wordno > 0)// this->LineInfo[lineno].getTotalWord()-1)
					 {
						 this->wordno--;
						 this->charno=this->LineInfo[lineno].Words[wordno].getTotalUnit()-1;
					 }


					 else
					 {
						 if(lineno > 0)
						 {
							 this->lineno--;
							 this->wordno=this->LineInfo[lineno].getTotalWord()-1;
							 this->charno=this->LineInfo[lineno].Words[wordno].getTotalUnit()-1;
						 
						 }
						 else
						 {
							 this->lineno=this->lineCount-1;
							 this->wordno=this->LineInfo[lineno].getTotalWord()-1;
							 this->charno=this->LineInfo[lineno].Words[wordno].getTotalUnit()-1;
						 }
					 }
				 }
				 this->display(this->lineno,this->wordno,this->charno);
				 this->Update();

		 }

private: System::Void addChar_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 int i = this->characterBox->SelectedIndex;
			 System::String* text ="";
			 int numOfElement = 0;
			 if(i>=0)
			 {
				 try
				 {
					 this->alForCharacters->Add(this->characterBox->SelectedItem->ToString());
					 //this->alForCharacters->Add(this->comboBoxCharacters->SelectedItem->ToString());
					 //numOfElement = alForCharacters->Count;

					 this->charEnumerator=this->alForCharacters->GetEnumerator();
					 //for(int j=0;j<numOfElement;j++)

					 while(this->charEnumerator->MoveNext())
					 {
						 //System::String* tmp=*dynamic_cast<__box String*>(this->charEnumerator->Current);
						 System::String* tmp=(String*)this->charEnumerator->Current;
						 text = text->Concat(text,tmp->ToString());
					 }
				 }
				 catch(System::Exception* ex)
				 {
					 System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Process Transcription Failed!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					 exit(0);
				 }
				 this->combineChar->Text = text;
			 }
			 /*if(numOfElement>0)
			 {
				 this->buttonCompleted->Enabled = true;
			 }*/



			 //this->combineChar->Text=this->combineChar->Text->Concat(this->combineChar->Text,this->characterBox->SelectedItem->ToString());
		 }

private: System::Void trainButton_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if(this->enableTrainingOnTextChanged ==true){
			 
				 System::Windows::Forms::MessageBox::Show(this->combineChar->Text);
			 TrainingProcess* tp=new TrainingProcess(this->applicationPath,this->ImageArray,this->x1,this->x2,this->y1,this->y2);
			 tp->PrepareTrainingData();
			 this->statusBar1->Text = "Training Please wait..";
			 this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			 tp->TrainingByHTK(tp->numOfFrame);
			 this->modelName = tp->GetTrainedModelName();

			 System::Windows::Forms::MessageBox::Show("Training Completed Successfully!","Success!!",MessageBoxButtons::OK,MessageBoxIcon::Exclamation);
			 
			 // delete the unnecessary temporary file
			 System::IO::File::Delete(wordToRec);

			 System::IO::StreamWriter* sw = System::IO::StreamWriter::Null;
			 System::String* tempStr;
			 try
			 {
				 
				 sw = System::IO::File::AppendText(this->modelTrainDBPath);
				 sw->WriteLine(this->modelName);


				 /*for(int i=0;i<this->alForCharacters->Count;i++)
				 {
					 tempStr = this->slForCharacters->GetByIndex(slForCharacters->IndexOfKey(alForCharacters[i]))->ToString();
					 sw->WriteLine(tempStr);
				 }*/

				 this->charEnumerator=this->alForCharacters->GetEnumerator();
					 //for(int j=0;j<numOfElement;j++)

				while(this->charEnumerator->MoveNext())
//				 for(int i=0;i<this->alForCharacters->Count;i++)
				 {
					 //System::String* tmp=*dynamic_cast<__box System::String*>(this->charEnumerator->Current);
					 System::String* tmp=(String*)this->charEnumerator->Current;
					 tempStr = this->slForCharacters->GetByIndex(slForCharacters->IndexOfKey(tmp))->ToString();
					 //tempStr = this->slForCharacters->GetByIndex(slForCharacters->IndexOfKey(this->charEnumerator->Current)->ToString());
					 sw->WriteLine(tempStr);
				 }
				 sw->WriteLine("*");
				 sw->Close();
				 this->characterBox->Text = "";
				 this->characterBox->SelectedIndex = -1;
				 //this->labelRecWord->Text = "";
				 this->alForCharacters->Clear();

				 // disable some buttons
				 //this->buttonCompleted->Enabled = false;
				 //this->groupBox1->Enabled = false;
				 
			 }
			 catch(System::Exception* ex)
			 {
				 System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Load the Model DataBase!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
				 exit(0);
			 }
			 
			 this->statusBar1->Text = "          Done    ";
			 this->Cursor = System::Windows::Forms::Cursors::Default;
			 bool enableTrainingOnTextChanged = false;
		 }
			 else{
				 System::Windows::Forms::MessageBox::Show("Nothing to Train.");
			 }
		 }

 

 

private: System::Void mnuExit_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->Close();
		 }

 

private: System::Void combineChar_TextChanged(System::Object *  sender, System::EventArgs *  e)
		 {
				this->enableTrainingOnTextChanged = true;
		 }

};
}