#pragma once

#include <string>
#include <memory>

enum class TypeKind {
    INT,
    FLOAT,
    STRING,
    BOOL,
    VOID,
    UNKNOWN
};

class Type {
public:
    Type(TypeKind kind) : kind(kind) {}
    virtual ~Type() = default;

    TypeKind getKind() const { return kind; }

    virtual std::string toString() const = 0;

    bool isNumeric() const {
        return kind == TypeKind::INT || kind == TypeKind::FLOAT;
    }

    bool isCompatibleWith(const Type* other) const {
        if (kind == TypeKind::UNKNOWN || other->kind == TypeKind::UNKNOWN) {
            return true;
        }
        if (kind == other->kind) {
            return true;
        }
        if (isNumeric() && other->isNumeric()) {
            return true;
        }
        return false;
    }

    static Type* commonType(Type* a, Type* b);

private:
    TypeKind kind;
};

class IntType : public Type {
public:
    IntType() : Type(TypeKind::INT) {}
    std::string toString() const override { return "int"; }
};

class FloatType : public Type {
public:
    FloatType() : Type(TypeKind::FLOAT) {}
    std::string toString() const override { return "float"; }
};

class StringType : public Type {
public:
    StringType() : Type(TypeKind::STRING) {}
    std::string toString() const override { return "string"; }
};

class BoolType : public Type {
public:
    BoolType() : Type(TypeKind::BOOL) {}
    std::string toString() const override { return "bool"; }
};

class VoidType : public Type {
public:
    VoidType() : Type(TypeKind::VOID) {}
    std::string toString() const override { return "void"; }
};

class UnknownType : public Type {
public:
    UnknownType() : Type(TypeKind::UNKNOWN) {}
    std::string toString() const override { return "unknown"; }
};

inline Type* Type::commonType(Type* a, Type* b) {
    if (!a || !b) return new UnknownType();
    if (a->getKind() == TypeKind::UNKNOWN || b->getKind() == TypeKind::UNKNOWN) {
        return new UnknownType();
    }
    if (a->getKind() == b->getKind()) {
        return a;
    }
    if (a->isNumeric() && b->isNumeric()) {
        if (a->getKind() == TypeKind::FLOAT || b->getKind() == TypeKind::FLOAT) {
            return new FloatType();
        }
        return new IntType();
    }
    return new UnknownType();
}
