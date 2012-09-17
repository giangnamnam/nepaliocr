
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
#include ".\externalpostprocessor.h"
 

externalPostProcessor::externalPostProcessor(System::String *applicationPath,System::String *PostProcessorApplicationFileName) //,System::String *inputFileName,System::String *outputFileName)
{
				// String *applicationPath = Application::StartupPath->ToString();
				 
				 applicationPath = applicationPath->Concat(applicationPath,"\\");
				 System::String *applicationName = applicationName->Concat(applicationPath,PostProcessorApplicationFileName);
				 this->outputFileName = System::String::Concat(applicationPath,"rawOutput.txt");

				 
				 try{
				 System::Diagnostics::Process *shellProcess = new System::Diagnostics::Process();
				 shellProcess->StartInfo->FileName = applicationName;
			  
				 
				 
				 shellProcess->StartInfo->CreateNoWindow = true;
				 shellProcess->StartInfo->RedirectStandardError = true;
				 shellProcess->StartInfo->UseShellExecute = false;
				 shellProcess->StartInfo->set_WorkingDirectory(applicationPath);
				 
				 //System::Windows::Forms::MessageBox::Show(shellProcess->StartInfo->get_WorkingDirectory()->ToString());
				 shellProcess->Start();
				 shellProcess->WaitForExit();
				// System::Windows::Forms::MessageBox::Show(applicationName,"running");
				 shellProcess->Close();
				/* if(shellProcess_Exited){
					 System::Windows::Forms::MessageBox::Show("exitted");
				 }*/
				 }
				 catch(System::Exception *ex){
					 System::Windows::Forms::MessageBox::Show(ex->ToString(),"Error running PostProcessor",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Error);
				 }


}
 

System::String* externalPostProcessor::getText(){
	return this->outputFileName;
}
void externalPostProcessor::tryNewProcesor(void){
	 // Start the child process.
	System::Diagnostics::Process *p1 = new System::Diagnostics::Process();
		// Redirect the output stream of the child process.
		p1->StartInfo->UseShellExecute = false;
		p1->StartInfo->RedirectStandardOutput = true;
		p1->StartInfo->FileName = "ocrTextProcessor.exe";
		p1->Start();
		// Do not wait for the child process to exit before
		// reading to the end of its redirected stream.
		// p.WaitForExit();
		// Read the output stream first and then wait.
		System::String *output = p1->StandardOutput->ReadToEnd();
		p1->WaitForExit();

}