#pragma once

#include <unordered_map>
#include <string>
#include "semantic/Symbol.h"

class Scope {
public:
    Scope(int level, Scope* parent = nullptr)
        : level(level), parent(parent), symbols() {}

    ~Scope() {
        for (auto& pair : symbols) {
            delete pair.second;
        }
    }

    bool define(Symbol* symbol) {
        if (symbols.find(symbol->getName()) != symbols.end()) {
            return false;
        }
        symbol->setScopeLevel(level);
        symbols[symbol->getName()] = symbol;
        return true;
    }

    Symbol* resolve(const std::string& name) {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return it->second;
        }
        if (parent) {
            return parent->resolve(name);
        }
        return nullptr;
    }

    bool contains(const std::string& name) const {
        return symbols.find(name) != symbols.end();
    }

    int getLevel() const { return level; }
    Scope* getParent() const { return parent; }
    void setParent(Scope* p) { parent = p; }

private:
    int level;
    Scope* parent;
    std::unordered_map<std::string, Symbol*> symbols;
};
