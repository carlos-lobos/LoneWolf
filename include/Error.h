#pragma once
#include <string>

struct Error {
    std::string message;
    int line;
    int column;

    Error(const std::string& msg, int l, int c)
        : message(msg), line(l), column(c) {}
};
