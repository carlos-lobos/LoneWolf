#pragma once
#include <vector>
#include "Error.h"

class ErrorCollector {
private:
    std::vector<Error> errors;

public:
    void addError(const std::string& message, int line, int column) {
        errors.emplace_back(message, line, column);
    }

    const std::vector<Error>& getErrors() const {
        return errors;
    }

    bool hasErrors() const {
        return !errors.empty();
    }
};
