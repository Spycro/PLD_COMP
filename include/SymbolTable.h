#pragma once
#include <unordered_map>
#include <memory>
#include "type/Type.h"
#include <string>
#include "SymbolTableElement.h"

typedef std::unordered_map<std::string, std::shared_ptr<SymbolTableElement>> SymbolMap;

class SymbolTable{
	public:
		SymbolTable() {}

		virtual ~SymbolTable() {}
		
		std::shared_ptr<SymbolTableElement> getSymbol(std::string name) { return elements->at(name) ; }
		void putSymbol(std::string name, std::shared_ptr<SymbolTableElement> symbol) { 
			elements->emplace(name, symbol);
		 }

		 std::string create_new_tempvar(Type* t);
		
		int get_var_index(std::string name);
		
		Type* get_var_type(std::string name);

		//const std::unique_ptr<SymbolMap> & getElements() { return elements; }

	private:
		std::unique_ptr<SymbolMap> elements;

};