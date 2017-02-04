#pragma once
#include <string>

class XmassTree
{
protected:
	int szerokosc;
public: 
	XmassTree(int x): szerokosc(x) {}
	virtual std::string draw()=0;
};
