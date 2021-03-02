#pragma once 

#include <string>

class Component
{
private:
	std::string name;
	
protected:
	
	Component(){}
	
public:
	void SetName(const char* n)
	{
		name = n;
	}
	
	const char* GetName()
	{
		return name.c_str();
	}
	
	virtual void InspectorUpdate() = 0;
};