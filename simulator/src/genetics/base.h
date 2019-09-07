#pragma once

class Base
{
public:
	Base();
	virtual Base* clone();
	bool typeInt;
	bool typeBool;
	bool typeFloat;
	bool dominant;
	bool enabled;
	int order;
};