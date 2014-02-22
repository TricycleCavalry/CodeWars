#ifndef _XML_WRAPPER_HEADER_
#define _XML_WRAPPER_HEADER_

#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLWrapper
{
public:
	XMLWrapper(void);
	~XMLWrapper(void);

	void OpenFile(const std::string& aFilePath);
	bool LoadDocument();
	
	void FindStartElement(const std::string& anElement);
	void FindChildElement(const std::string& anElement);
	bool CheckElement(const std::string& anElement);
	bool CheckNextElement();
	bool CheckChildElement();
	void GoToParentElement();
	void GoToChildElement();
	void NextElement();
	void SearchForElement(const std::string& anElement);

	tinyxml2::XMLNode* GetChildNode(const std::string& anElement);
	tinyxml2::XMLNode* GetNode();

	void LoadNode(tinyxml2::XMLNode* aNode);

	int GetElementInt(const std::string& anElement);
	float GetElementFloat(const std::string& anElement);
	double GetElementDouble(const std::string& anElement);
	std::string GetElementString(const std::string& anElement);
	std::string GetElementName();

	int GetInt();
	float GetFloat();
	double GetDouble();
	std::string GetString();

	void PrintError();


private:
	tinyxml2::XMLDocument* myDocument;
	tinyxml2::XMLNode* myCurrentNode;
	tinyxml2::XMLElement* myCurrentElement;
};

#endif