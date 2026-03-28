#pragma once

#include <string>
#include <vector>
#include "semantic/Type.h"

enum class SymbolKind {
    VARIABLE,
    FUNCTION,
    PARAMETER
};

class Symbol {
public:
    Symbol(const std::string& name, Type* type, SymbolKind kind)
        : name(name), type(type), kind(kind), scopeLevel(0) {}

    virtual ~Symbol() {
        delete type;
    }

    const std::string& getName() const { return name; }
    Type* getType() const { return type; }
    SymbolKind getKind() const { return kind; }
    int getScopeLevel() const { return scopeLevel; }

    void setScopeLevel(int level) { scopeLevel = level; }

private:
    std::string name;
    Type* type;
    SymbolKind kind;
    int scopeLevel;
};

class VariableSymbol : public Symbol {
public:
    VariableSymbol(const std::string& name, Type* type)
        : Symbol(name, type, SymbolKind::VARIABLE) {}
};

class FunctionSymbol : public Symbol {
public:
    FunctionSymbol(const std::string& name, Type* returnType)
        : Symbol(name, returnType, SymbolKind::FUNCTION), parameters() {}

    void addParameter(VariableSymbol* param) {
        parameters.push_back(param);
    }

    const std::vector<VariableSymbol*>& getParameters() const { return parameters; }

private:
    std::vector<VariableSymbol*> parameters;
};
