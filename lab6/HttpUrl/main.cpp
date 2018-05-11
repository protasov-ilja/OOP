// HttpUrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <iostream>

int main()
{
	std::string inputUrl;
	while (getline(std::cin, inputUrl))
	{
		try
		{
			//CHttpUrl url(inputUrl);
			CHttpUrl url("www.mysite.com", "/docs", Protocol::HTTP, 32);
			std::cout << "\n> Porotocol: " << url.GetStringFromProtocol()
				<< "\n> Domain: " << url.GetDomain()
				<< "\n> Port: " << url.GetPort()
				<< "\n> Document: " << url.GetDocument() << std::endl;
		}
		catch (const CUrlParsingError& err)
		{
			std::cout << err.GetMessage() << std::endl;
 		}
	}

    return 0;
}

