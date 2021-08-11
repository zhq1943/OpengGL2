#pragma once
#include<stdio.h>
#include<direct.h>
#include<string>
#include<iostream>

class  Chelp
{
public:
	 Chelp();
	~ Chelp();
	static std::string getDirectory();
private:

};

 Chelp:: Chelp()
{
}

 Chelp::~ Chelp()
{
}

 inline std::string Chelp::getDirectory()
 {
	 char* buffer;
	 if ((buffer = _getcwd(NULL,0)) == NULL)
	 {
		 return std::string();
	 }

	 std::string path(buffer);
	 return path;
 }
