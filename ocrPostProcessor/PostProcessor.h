#pragma once

public __gc class PostProcessor
{
public:
	PostProcessor(System::String *tempStr);
	System::String* TextPostProcessor(void);
	
	~PostProcessor(void);

private:bool IsDependentVowel(unsigned short Vowel);
private: System::String *processStr;
};
