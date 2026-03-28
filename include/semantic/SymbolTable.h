#pragma once

#include "semantic/Scope.h"
#include "semantic/Symbol.h"

class SymbolTable {
public:
    SymbolTable() 
        : currentScope(nullptr), scopeLevel(0) {
        currentScope = new Scope(0);
    }

    ~SymbolTable() {
        delete currentScope;
    }

    void enterScope() {
        scopeLevel++;
        currentScope = new Scope(scopeLevel, currentScope);
    }

    void exitScope() {
        if (currentScope->getParent()) {
            Scope* old = currentScope;
            currentScope = currentScope->getParent();
            old->setParent(nullptr);
            delete old;
            scopeLevel--;
        }
    }

    bool define(Symbol* symbol) {
        return currentScope->define(symbol);
    }

    Symbol* resolve(const std::string& name) {
        return currentScope->resolve(name);
    }

    bool isDefined(const std::string& name) {
        return currentScope->resolve(name) != nullptr;
    }

    int getCurrentScopeLevel() const {
        return scopeLevel;
    }

    Scope* getCurrentScope() const {
        return currentScope;
    }

private:
    Scope* currentScope;
    int scopeLevel;
};
