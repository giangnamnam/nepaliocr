#include "TrainingForm.h"
#include "ThresholedValue.h"
#include "rgbConvert.h"
#include "Separate.h"
#include "Convolution.h"
#include "Deskew.h"



#pragma once


namespace Exercise1
{
	using namespace System;
	using namespace System::Data;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Drawing::Imaging;

	/// <summary> 
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	
	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			//user declarations
			this->BinaryDone=false;
			this->ImageLoaded=false;
			this->SeparateDone=false;
//			num_bins=256;

			
			InitializeComponent();
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



	//user variable start 
	private: Bitmap* im;
	private: Bitmap* BinaryImage;

	private: Graphics* g;

	private: int intLevel;
	private: int **ImgArray;

	private: bool **BArray;
			 bool **tmpBArray;
	private: bool BinaryDone;
	private: bool ImageLoaded;
			 bool SeparateDone;

	private: int numberOfLines;
	private: Line* Lines; 
			 
	
	//private: Graphics* g;	
//    private: BinaryImgProcessor* bim;
    //user variable end 
	
	private: System::Windows::Forms::Panel *  picture_panel;
	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::Button *  convertToBinary_button;
	private: System::Windows::Forms::Button *  openImage;
	private: System::Windows::Forms::OpenFileDialog *  openImageDialog;
	private: System::Windows::Forms::Button *  separate_button;
	private: System::Windows::Forms::SaveFileDialog *  saveImageDialog;
	private: System::Windows::Forms::Button *  saveImage;
	private: System::Windows::Forms::Button *  imContrast;
	private: System::Windows::Forms::Button *  meanRemoval;
	private: System::Windows::Forms::Button *  deSkew;
	private: System::Windows::Forms::Button *  train;




			 /// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container * components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->convertToBinary_button = new System::Windows::Forms::Button();
			this->picture_panel = new System::Windows::Forms::Panel();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->openImage = new System::Windows::Forms::Button();
			this->openImageDialog = new System::Windows::Forms::OpenFileDialog();
			this->separate_button = new System::Windows::Forms::Button();
			this->saveImageDialog = new System::Windows::Forms::SaveFileDialog();
			this->saveImage = new System::Windows::Forms::Button();
			this->imContrast = new System::Windows::Forms::Button();
			this->meanRemoval = new System::Windows::Forms::Button();
			this->deSkew = new System::Windows::Forms::Button();
			this->train = new System::Windows::Forms::Button();
			this->picture_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// convertToBinary_button
			// 
			this->convertToBinary_button->Cursor = System::Windows::Forms::Cursors::Hand;
			this->convertToBinary_button->Location = System::Drawing::Point(342, 80);
			this->convertToBinary_button->Name = S"convertToBinary_button";
			this->convertToBinary_button->Size = System::Drawing::Size(72, 24);
			this->convertToBinary_button->TabIndex = 5;
			this->convertToBinary_button->Text = S"BINARY";
			this->convertToBinary_button->Click += new System::EventHandler(this, close_button_Click_1);
			// 
			// picture_panel
			// 
			this->picture_panel->AutoScroll = true;
			this->picture_panel->BackColor = System::Drawing::Color::AliceBlue;
			this->picture_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->picture_panel->Controls->Add(this->pictureBox1);
			this->picture_panel->Location = System::Drawing::Point(8, 128);
			this->picture_panel->Name = S"picture_panel";
			this->picture_panel->Size = System::Drawing::Size(776, 384);
			this->picture_panel->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(5, 12);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 100);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// openImage
			// 
			this->openImage->BackColor = System::Drawing::Color::Transparent;
			this->openImage->Cursor = System::Windows::Forms::Cursors::Hand;
			this->openImage->Location = System::Drawing::Point(224, 8);
			this->openImage->Name = S"openImage";
			this->openImage->Size = System::Drawing::Size(112, 48);
			this->openImage->TabIndex = 1;
			this->openImage->Text = S"OPEN IMAGE";
			this->openImage->Click += new System::EventHandler(this, openImage_Click);
			// 
			// openImageDialog
			// 
			this->openImageDialog->DefaultExt = S"*.jpg";
			this->openImageDialog->Filter = S" \"JPEG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png|GIF Files (*.gif)|*.gif\"";
			// 
			// separate_button
			// 
			this->separate_button->Cursor = System::Windows::Forms::Cursors::Hand;
			this->separate_button->Location = System::Drawing::Point(461, 80);
			this->separate_button->Name = S"separate_button";
			this->separate_button->TabIndex = 6;
			this->separate_button->Text = S"SEPARATE";
			this->separate_button->Click += new System::EventHandler(this, separate_button_Click);
			// 
			// saveImageDialog
			// 
			this->saveImageDialog->DefaultExt = S"*.jpg";
			// 
			// saveImage
			// 
			this->saveImage->BackColor = System::Drawing::Color::WhiteSmoke;
			this->saveImage->Location = System::Drawing::Point(424, 8);
			this->saveImage->Name = S"saveImage";
			this->saveImage->Size = System::Drawing::Size(112, 48);
			this->saveImage->TabIndex = 2;
			this->saveImage->Text = S"SAVE IMAGE";
			this->saveImage->Click += new System::EventHandler(this, saveImage_Click);
			// 
			// imContrast
			// 
			this->imContrast->BackColor = System::Drawing::Color::Transparent;
			this->imContrast->Cursor = System::Windows::Forms::Cursors::Hand;
			this->imContrast->Location = System::Drawing::Point(96, 80);
			this->imContrast->Name = S"imContrast";
			this->imContrast->TabIndex = 3;
			this->imContrast->Text = S"CONTRAST";
			this->imContrast->Click += new System::EventHandler(this, imContrast_Click);
			// 
			// meanRemoval
			// 
			this->meanRemoval->Cursor = System::Windows::Forms::Cursors::Hand;
			this->meanRemoval->Location = System::Drawing::Point(222, 80);
			this->meanRemoval->Name = S"meanRemoval";
			this->meanRemoval->TabIndex = 4;
			this->meanRemoval->Text = S"MEAN";
			this->meanRemoval->Click += new System::EventHandler(this, meanRemoval_Click);
			// 
			// deSkew
			// 
			this->deSkew->Cursor = System::Windows::Forms::Cursors::Hand;
			this->deSkew->Location = System::Drawing::Point(578, 79);
			this->deSkew->Name = S"deSkew";
			this->deSkew->TabIndex = 7;
			this->deSkew->Text = S"DE-SKEW";
			this->deSkew->Click += new System::EventHandler(this, deSkew_Click);
			// 
			// train
			// 
			this->train->Location = System::Drawing::Point(701, 80);
			this->train->Name = S"train";
			this->train->TabIndex = 8;
			this->train->Text = S"Train";
			this->train->Click += new System::EventHandler(this, train_Click);
			// 
			// Form1
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::Application;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(794, 518);
			this->Controls->Add(this->train);
			this->Controls->Add(this->meanRemoval);
			this->Controls->Add(this->imContrast);
			this->Controls->Add(this->saveImage);
			this->Controls->Add(this->separate_button);
			this->Controls->Add(this->openImage);
			this->Controls->Add(this->picture_panel);
			this->Controls->Add(this->convertToBinary_button);
			this->Controls->Add(this->deSkew);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = S"Form1";
			this->Text = S" Image Processing Part Of Nepali OCR";
			this->TopMost = false;
			this->picture_panel->ResumeLayout(false);
			this->ResumeLayout(false);

		}	


		
		public: void Conv3x3(ConvMatrix* m)
		{
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			
			try{
			// Avoid divide by zero errors
			if (0 == m->Factor) return;

			Bitmap* bSrc = (Bitmap*)im->Clone(); 

			// GDI+ still lies to us - the return format is BGR, NOT RGB.
			BitmapData* bmData = im->LockBits(Rectangle(0, 0, im->Width, im->Height), ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);
			BitmapData* bmSrc = bSrc->LockBits(Rectangle(0, 0, bSrc->Width, bSrc->Height), ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);

			int stride = bmData->Stride;
			int stride2 = stride * 2;
			IntPtr Scan0 = bmData->Scan0;
			IntPtr SrcScan0 = bmSrc->Scan0;

				Byte * p = (Byte *)(void *)Scan0;
				Byte * pSrc = (Byte *)(void *)SrcScan0;

				int nOffset = stride - im->Width*3;
				int nWidth = im->Width - 2;
				int nHeight = im->Height - 2;

				int nPixel;

				for(int y=0;y < nHeight;++y)
				{
					for(int x=0; x < nWidth; ++x )
					{
						nPixel = ( ( ( (pSrc[2] * m->TopLeft) + (pSrc[5] * m->TopMid) + (pSrc[8] * m->TopRight) +
							(pSrc[2 + stride] * m->MidLeft) + (pSrc[5 + stride] * m->Pixel) + (pSrc[8 + stride] * m->MidRight) +
							(pSrc[2 + stride2] * m->BottomLeft) + (pSrc[5 + stride2] * m->BottomMid) + (pSrc[8 + stride2] * m->BottomRight)) / m->Factor) + m->Offset); 

						if (nPixel < 0) nPixel = 0;
						if (nPixel > 255) nPixel = 255;

						p[5 + stride]= (Byte)nPixel;

						nPixel = ( ( ( (pSrc[1] * m->TopLeft) + (pSrc[4] * m->TopMid) + (pSrc[7] * m->TopRight) +
							(pSrc[1 + stride] * m->MidLeft) + (pSrc[4 + stride] * m->Pixel) + (pSrc[7 + stride] * m->MidRight) +
							(pSrc[1 + stride2] * m->BottomLeft) + (pSrc[4 + stride2] * m->BottomMid) + (pSrc[7 + stride2] * m->BottomRight)) / m->Factor) + m->Offset); 

						if (nPixel < 0) nPixel = 0;
						if (nPixel > 255) nPixel = 255;
							
						p[4 + stride] = (Byte)nPixel;

						nPixel = ( ( ( (pSrc[0] * m->TopLeft) + (pSrc[3] * m->TopMid) + (pSrc[6] * m->TopRight) +
							(pSrc[0 + stride] * m->MidLeft) + (pSrc[3 + stride] * m->Pixel) + (pSrc[6 + stride] * m->MidRight) +
							(pSrc[0 + stride2] * m->BottomLeft) + (pSrc[3 + stride2] * m->BottomMid) + (pSrc[6 + stride2] * m->BottomRight)) / m->Factor) + m->Offset); 

						if (nPixel < 0) nPixel = 0;
						if (nPixel > 255) nPixel = 255;

						p[3 + stride] = (Byte)nPixel;

						p += 3;
						pSrc += 3;
					}
					p += nOffset;
					pSrc += nOffset;
				}
			
			im->UnlockBits(bmData);
			bSrc->UnlockBits(bmSrc);

			this->pictureBox1->Image = im;
			g=this->pictureBox1->CreateGraphics();
			System::Windows::Forms::MessageBox::Show("Mean Removal Done!!!!"/*fLevel.ToString()*/,"Threshold Value");
			}
		catch(Exception* ex)
			{
				System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Apply Mean Removal!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
			}
		this->Cursor = System::Windows::Forms::Cursors::Default;
			
		}
		
		private: void MeanRemoval(int nWeight)
		{
			ConvMatrix* m=new ConvMatrix();
			//ConvMatrix* h1[];
			//h1=new ConvMatrix* [20];
			//h1=this->GetTopValR();
			
			m->SetAll(-1);
			m->Pixel=nWeight;
			m->Factor=nWeight-8;
			this->Conv3x3(m);
		}

		/*private: ConvMatrix* GetTopValR()[]
				 {
					ConvMatrix* h1[];
					h1=new ConvMatrix* [20];
			
					return h1;
				 }
		 */
		private: void Contrast(int nContrast)
		{
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			try{
			double pixel = 0, contrast = (100.0+nContrast)/100.0;

			contrast *= contrast;

			int red, green, blue;
			
			// GDI+ still lies to us - the return format is BGR, NOT RGB.
			BitmapData* bmData = im->LockBits(Rectangle(0, 0, im->Width, im->Height), ImageLockMode::ReadWrite, PixelFormat::Format24bppRgb);
			int stride = bmData->Stride;
			IntPtr Scan0 = bmData->Scan0;
			
			//System::Byte p;
			Byte* p = (Byte*)(void *)Scan0;
			
			
				//Color clr = b->GetPixel(i,j);
				//int p= clr.ToArgb();				
			
				int nOffset = stride - im->Width*3;

				for(int y=0;y<im->Height;++y)
				{
					for(int x=0; x < im->Width; ++x )
					{
						blue = p[0];
						green = p[1];
						red = p[2];
				
						pixel = red/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[2] = (Byte) pixel;

						pixel = green/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[1] = (Byte) pixel;

						pixel = blue/255.0;
						pixel -= 0.5;
						pixel *= contrast;
						pixel += 0.5;
						pixel *= 255;
						if (pixel < 0) pixel = 0;
						if (pixel > 255) pixel = 255;
						p[0] = (Byte) pixel;					

						p += 3;
					}
					p += nOffset;
				}
			

			im->UnlockBits(bmData);
			
			this->pictureBox1->Image = im;
			g=this->pictureBox1->CreateGraphics();
			System::Windows::Forms::MessageBox::Show("Contrast Done!!!!"/*fLevel.ToString()*/,"Threshold Value");
			}
		catch(Exception* ex)
			{
				System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Improve the Contrast!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
			}
		this->Cursor = System::Windows::Forms::Cursors::Default;

//			return true;
		}
		private: void makeBinary()
			 {
				 if(this->ImageLoaded)
				 {
					//if (this->BinaryDone)
					//	return;
				 
					this->BinaryDone = true;
					
					try{
					 // set the cursor to wait.... 
						this->Cursor = System::Windows::Forms::Cursors::WaitCursor;

					 
					 // calculating Thresholed Value for binary image					 
						ThresholedValue* ts = new ThresholedValue(im);
						float fLevel = ts->GetThresholed();
						intLevel = int(fLevel*255);
					
					 
					 
					 // getting an binary array of 					 
						rgbConvert* rgbC = new rgbConvert(im);
						BArray = rgbC->GetBinaryArray(200);
						ImgArray = rgbC->GetImageArray( );
					   	
					 // Showing the binary image
						this->BinaryImage = rgbC->GetBinaryImage();
						this->pictureBox1->Image = this->BinaryImage;
						
					 // set the cursor to Default.... 
						this->Cursor = System::Windows::Forms::Cursors::Default;
						System::Windows::Forms::MessageBox::Show(this->intLevel.ToString()/*fLevel.ToString()*/,"Threshold Value");
					}
				 catch(System::Exception* ex)
					{
					System::Windows::Forms::MessageBox::Show(ex->Message->ToString(),"Failed to Binarize the Image!!",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
					this->Update();
					}
				 this->Update();
				 }
	}// end of function 


		private: void openImageFile()
			{
				System::Windows::Forms::DialogResult d = this->openImageDialog->ShowDialog();
				if (d == System::Windows::Forms::DialogResult::OK)				 
				 {			 
					this->BinaryDone = false;
					this->SeparateDone=false;
					this->ImageLoaded = true;
					// creating a bitmap
					im = new Bitmap(this->openImageDialog->OpenFile());
					this->pictureBox1->Image = im;
					g=this->pictureBox1->CreateGraphics();
				 }
				this->Update();
				 
			}
		private: void saveImageFile()
			{
				if(this->BinaryDone)
				{	
					saveImageDialog->Filter= "Jpeg files (*.jpg)|*.jpg|PNG files (*.png)|*.png|All valid files (*.jpg/*.png)|*.jpg/*.png" ;
					saveImageDialog->FilterIndex = 1 ;
					saveImageDialog->RestoreDirectory = true ;

					System::Windows::Forms::DialogResult d = this->saveImageDialog->ShowDialog();
						if (d == System::Windows::Forms::DialogResult::OK)				 
							{			 
							// creating a bitmap
							Bitmap* save;
							save=new Bitmap(this->pictureBox1->Image);
							save->Save(saveImageDialog->FileName);
							
							}
				}
				 
			}

		
		private: void separateChar()
				 {
					 Pen* p=new Pen(Color::Blue,1);
	
								for(int i=0;i<this->numberOfLines;i++)
									{
										for(int j=0;j<this->Lines[i].getTotalWord();j++)
											{
												for(int k=0;k<this->Lines[i].Words[j].getTotalUnit();k++)
													{
														int x1=this->Lines[i].Words[j].Units[k].getStartColumn();
														int x2=this->Lines[i].Words[j].Units[k].getEndColumn();
														int y1=this->Lines[i].getStartRow();
														int y2=this->Lines[i].getEndRow();

														g->DrawLine(p,x1,y1,x1,y2);
														g->DrawLine(p,x2,y1,x2,y2);
													}
											}
									}

				 }
		private: void separate()
				 {
					 this->tmpBArray=new bool*[im->Height];
					 //this->tmpBArray=this->BArray;
					 for(int i=0;i<im->Height;i++)
					 {
						 this->tmpBArray[i]=new bool[im->Width];
						 for(int j=0;j<im->Width;j++)
						 {
							 this->tmpBArray[i][j]=this->BArray[i][j];
						 }

					 }
					 if(this->BinaryDone)
						{

							if(this->SeparateDone==false)
							{
							Separate* sp=new Separate(im,BArray,g);
							sp->LineSeparate();

							this->numberOfLines=sp->getNumberOfLines();
							this->Lines=sp->getLines();
							this->SeparateDone=true;
							this->separateChar();							
							}

							else
							{
								this->separateChar();
							}







							//sp->drawHorizontalHist();
							//Pen* p=new Pen(Color::Red,1);
							//g->DrawLine(p,50,50,150,150);
							//g->DrawRectangle(p,50,50,150,150);//x,y,width,height
						}
					this->Update();
				 }
		private: void doDeSkew()
				  {
					  Deskew* ds=new Deskew(im);
					  double skewAngle=ds->GetSkewAngle();
					  System::Windows::Forms::MessageBox::Show(skewAngle.ToString(),"Skew Angle");
					  im=this->RotateImage(-skewAngle); 
					  this->pictureBox1->Image = im;
				  }
		private: Bitmap* RotateImage(double angle)
					{
						Graphics* gr;
						Bitmap* tmp=new Bitmap(im->Width,im->Height,PixelFormat::Format24bppRgb);
						tmp->SetResolution(im->HorizontalResolution,im->VerticalResolution);
						gr=Graphics::FromImage(tmp);
						gr->FillRectangle(Brushes::White,0,0,im->Width+400,im->Height+400);
						gr->RotateTransform(angle);
						gr->DrawImage(im,15,0);
						gr->Dispose();
						return tmp;
					}

private: System::Void close_button_Click_1(System::Object *  sender, System::EventArgs *  e)
			 {
				//this->Dispose(true);
				this->makeBinary();
			 }


private: System::Void openImage_Click(System::Object *  sender, System::EventArgs *  e)
			{
				this->openImageFile();
			}

private: System::Void separate_button_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->separate();
		 }

private: System::Void saveImage_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->saveImageFile();
		 }

private: System::Void imContrast_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			this->Contrast(10);
			this->Update();
		 }

private: System::Void meanRemoval_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->MeanRemoval(9);
			 this->Update();
		 }

private: System::Void deSkew_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->doDeSkew();
		 }

private: System::Void train_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 OCR::TrainingForm* tw=new OCR::TrainingForm();
			 tw->defineVar(this->tmpBArray,this->Lines,this->numberOfLines);
			 tw->ShowDialog();


			 //TrainWindow* tr=new TrainWindow();
			
		 }

};




}


