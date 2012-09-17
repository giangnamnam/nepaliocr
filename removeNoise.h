
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
using namespace System::Drawing;

public __gc class removeNoise
{
private: 
	System::Drawing::Bitmap* fohorImage; //the noisy image that will be imported 
	System::Drawing::Bitmap* safaImage; //the image that will be exported
	int xsize; //image width
	int ysize; //image height
	int **fohorImageKoArray; //A two dimentional integer array of original image
	int **window; //jhyal grr b2 tungbaria grrbaria Grr GEEEEE AAARRRRRE Aree	
	int k; //size of window 
	int stRwIndx; //start row index.
	int edRwIndx; //End row index
    int stClIndx; //Start column index
	int edClIndx; //End column index
	int numFill; // FLAG to be set or reset 
	int det;//color to be filled
	int pass; //FLAG (which will be set or reset depending upon conditions)
	int n;  //Number of white surrounding pixels
	int c; //Number of connected components
	int r; //Number of white corner pixels in the window(jhyal)
		
public:
	//public constructor removeNoise : that will be called by default
	//Parameters passed : A noisy image and A two dimensional integer array of the image
	removeNoise(System::Drawing::Bitmap* BinaryImage, int **ImgArray)
	{
		
	
		fohorImage = BinaryImage; //importing this->fohorimage = image imported 
		fohorImageKoArray = ImgArray; //importingthis->fohorImagekoArray = Array imported
		xsize = fohorImage->Width; //importing width
		ysize = fohorImage->Height; //importing height

		//safaImage = new Bitmap(xsize, ysize, Imaging::PixelFormat::Format24bppRgb);
		safaImage=fohorImage;

		k=3;//window size
		stRwIndx = 2;
		edRwIndx = ysize - (k-2);// end row index=height-(1)
		stClIndx = 2;// start column index=2
		edClIndx = xsize - (k-2);// end column index=width-(1)
		numFill=0;
		det=1;//fill color
		pass=0;

		//initializing window to size 3*3  
		window = new int * [k];
		for (int i = 0; i < k; i++)
		{
			window[i] = new int[k];
		}
	}

	System::Drawing::Bitmap* GetClearImage ()
	{
		while(1)
		{
			numFill=0;
			for(int i=stRwIndx; i < edRwIndx; i++)//every row of picture starting from row 2
			{
				for(int j=stClIndx; j < edClIndx; j++)//every column of the row starting from column 2
				{
			
					if(fohorImageKoArray[i][j] == 0)//if pixel is black
					{
						for(int rowOfImage=(i-1),int rowOfWindow=0; rowOfImage<=(i+1),rowOfWindow<=2;rowOfImage++,rowOfWindow++)
						{//to extract window 
							for(int colOfImage=(j-1),int colOfWindow=0; colOfImage<=(j+1),colOfWindow <=2; colOfImage++,colOfWindow ++)
							{//to extract window 
								window[rowOfWindow][ colOfWindow]=fohorImageKoArray[rowOfImage][colOfImage];
								
							}
						}
						pass = this -> ncr_test(window,det);
						if(pass == 1)
						{
							fohorImageKoArray[i][j] = det;
							this->safaImage->SetPixel(j,i,Color::White);
							numFill = 1;
                        }
					}//if(fohorImageKoArray[i][j] == 0) end
				}//for(int j=stClIndx; j < edClIndx; j++) end
			}//for(int i=stRwIndx; i < edRwIndx; i++) end
			numFill = 0;
			if(numFill==0)
				break;
			
		}
		return safaImage;
	}//getClearImage end
	
	int ncr_test(int **window, int det)
	{
		int returngarneyvalue;
		n=this->nValue(window,det);
		
		c=this->cValue(window,det);
		r=this->rValue(window,det);
	
		
		if (c==1)
		{
			if(n>((3*k)-4))
				returngarneyvalue=1;
			if(n == ((3*k)-4) &&  (r==2))
			    returngarneyvalue=1;
			if(n<((3*k)-4))
				returngarneyvalue=0;

		}
		else
			returngarneyvalue=0;

	
	return returngarneyvalue;
	}

	 
	int nValue(int **window, int det)
	{
		int nreturn = 0;
			
		if(window[0][0]== det)
			nreturn=nreturn + 1;
		if(window[0][1]== det)
			nreturn=nreturn + 1;
		if(window[0][2]== det)
			nreturn=nreturn + 1;
		if(window[1][0]== det)
			nreturn=nreturn + 1;
		if(window[1][2]== det)
			nreturn=nreturn + 1;
		if(window[2][0]== det)
			nreturn=nreturn + 1;
		if(window[2][1]== det)
			nreturn=nreturn + 1;
		if(window[2][2]== det)
			nreturn=nreturn + 1;

		return nreturn;
	}

		
	int  cValue(int **window, int det)
	{
		int c = 0;
		int conT = 0;
		for ( int x = 0; x <=2; x++)
		{
			for ( int y = 0; y <=2; y++)
			{
				if(window[x][y] != det)
					conT = 0;
				else
				{
					if ( x == 0)
					{
						if(conT==0)
						{
							c = c + 1;
							conT = 1;
						}
					}
					else
					{
						if(x==2)
						{
							if(y==0)
							{
								if(window[x-1][y]==det)
									conT=1;
								else
								{
									c=c+1;
									conT=1;
								}
							}
							else
							{
								if(y==2 && window[x-1][y]==det)
								{
									if(conT==1 && c>1)
										c=c-1;
								}
								else
								{
									if(conT == 0)
									{
										c=c+1;
										conT=1;
									}
								}
							}
						}
						else
						{
							if((y==0 || y==2) && window[x-1][y]!=det)
								c=c+1;
							
						}
					}
				}
			}
		}
		return c;
	}
		 
	int rValue(int **window, int det)
	{
		int rreturn=0;

		if(window[0][0]==det)
			rreturn = rreturn+1;

		if(window[0][2]==det)
			rreturn = rreturn+1;

		if(window[2][0]==det)
            rreturn = rreturn+1;

		if(window[2][2]==det)
			rreturn = rreturn+1;
		
		return rreturn;
        
	}

};
