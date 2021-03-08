#pragma once
#include <unordered_map>

typedef symbolTableElement {
	std::string type;
	bool isSet;
	bool isUsed;
	int memoryOffset;
} symbolTableElement;


class SymbolTable{
	public:
		SymbolTable() {}

		virtual ~SymbolTable() {}
		

		std::unordered_map<symbolTableElement> getElements() { return elements; }

	private:
		std::unordered_map<symbolTableElement> elements;


};