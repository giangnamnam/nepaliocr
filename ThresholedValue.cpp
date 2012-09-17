
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

#include "ThresholedValue.h"

using namespace System;
using namespace System::Collections;


ThresholedValue::ThresholedValue(System::Drawing::Bitmap* bm)
{
	ImageFile = bm;

	xsize = ImageFile->Width;
	ysize = ImageFile->Height;
}

void ThresholedValue::ImHist()
{	
	counts = new float[256];
	for (int i = 0; i < 256; i++ )
		counts[i] = 0;

	int max = 0;
	for( int i = 0; i < xsize; i++ )
		for ( int j = 0; j < ysize; j++ ){
			System::Drawing::Color clr = ImageFile->GetPixel(i,j);
			int pixel = clr.ToArgb();				
			
			//int alpha = (pixel >> 24) & 0xff;// no need here
			/*int red = (pixel >> 16) & 0xff;
			counts[red]++;

			int green = (pixel >>  8) & 0xff;
			counts[green]++;

			int blue = (pixel      ) & 0xff;
			counts[blue]++;*/

			counts[(pixel >> 16) & 0xff]++; //red			
			counts[(pixel >>  8) & 0xff]++;	//green		
			counts[(pixel      ) & 0xff]++; //blue
			//
		}// inner for*/
}// end of function ImHist()




void ThresholedValue::calculateValue()
{
	int i;        
	sum_counts = 0;
	
	
	for( i = 0; i < /*sizeof(counts)*/256; i++ ){
		//System.out.println(counts[i]);
		sum_counts += counts[i];
	}        

	p = new float[256];
	omega = new float[256];
	mu = new float[256];

	p[0] = counts[0]/sum_counts;
	omega[0] = p[0];        
	mu[0] = p[0]*1;

	for( i = 1; i < /*sizeof(counts)*/256; i++ ){
		p[i] = counts[i]/sum_counts;
		omega[i] = omega[i-1] + p[i]; //cumulative sum
		mu[i] = mu[i-1] + p[i]*(i+1); //cumulative sum
	}
	mu_t = mu[255];
}//end of function calculateValue()


float ThresholedValue::GetThresholed()
{
	ImHist();
	calculateValue();
	float level = 0;
	double *sigma_b_squared;
	sigma_b_squared = new double[256];
	double maxval = 0;
	//float sigma_b_squared = (mu_t * omega - mu).^2 ./ (omega .* (1 - omega));

	for (int i = 0; i < 255; i++ ){
		float div = omega[i] * (1 - omega[i]);
		//System.out.println("div  " + div);
		if (div == 0)
			sigma_b_squared[i] = -1;
		else
		{
			float tmp = (mu_t * omega[i] - mu[i]);
			sigma_b_squared[i] = (tmp*tmp)/div;
		}

		if (maxval < sigma_b_squared[i] )
			maxval = sigma_b_squared[i];
	}// end of for */

	/**
	*Find the location of the maximum value of sigma_b_squared.
	*The maximum may extend over several bins, so average together the
	*locations.  If maxval is NaN, meaning that sigma_b_squared is all NaN,
	*then return 0.
	*/
	int count = 0;
	int sumI = 0;

	if (maxval > -1 ){
		for (int i = 0; i < 256; i++){
			if(maxval == sigma_b_squared[i] ){
				sumI += i+1;
				count++;
			}
		}//end of for
		float idx = sumI/count;
		level = (idx - 1)/(num_bins-1);
	}// end of if
	else
		level = 0;

	return level;
}
