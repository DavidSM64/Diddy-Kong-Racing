#pragma once

#include <string>
#include <arpa/inet.h> // for ntohs() etc.
#include <stdint.h>

class be_uint16_t {
public:
        be_uint16_t() : be_val_(0) {
        }
        // Transparently cast from uint16_t
        be_uint16_t(const uint16_t &val) : be_val_(htons(val)) {
        }
        // Transparently cast to uint16_t
        operator uint16_t() const {
            return ntohs(be_val_);
        }
private:
        uint16_t be_val_;
} __attribute__((packed));

class be_uint32_t {
public:
        be_uint32_t() : be_val_(0) {
        }
        // Transparently cast from uint16_t
        be_uint32_t(const uint32_t &val) : be_val_(htonl(val)) {
        }
        // Transparently cast to uint16_t
        operator uint32_t() const {
            return ntohl(be_val_);
        }
private:
        uint32_t be_val_;
} __attribute__((packed));

class be_int16_t {
public:
        be_int16_t() : be_val_(0) {
        }
        // Transparently cast from int16_t
        be_int16_t(const int16_t &val) : be_val_(htons(val)) {
        }
        // Transparently cast to int16_t
        operator int16_t() const {
                return ntohs(be_val_);
        }
private:
        int16_t be_val_;
} __attribute__((packed));

class be_int32_t {
public:
        be_int32_t() : be_val_(0) {}
        // Transparently cast from int32_t
        be_int32_t(const int32_t &val) : be_val_(htonl(val)) {
        }
        // Transparently cast to int32_t
        operator int32_t() const {
            return ntohl(be_val_);
        }
private:
        int32_t be_val_;
} __attribute__((packed));

// Removes type-punning warning.
union floatInt {
    uint32_t i;
    float f;
};

class be_float {
public:
        be_float() : be_val_(0.0f) {}
        be_float(float val) {
            floatInt floatAsInt;
            floatAsInt.f = val;
            floatAsInt.i = htonl(floatAsInt.i);
            be_val_ = floatAsInt.f;
        }
        operator float() const {
            floatInt floatAsInt;
            floatAsInt.f = be_val_;
            floatAsInt.i = ntohl(floatAsInt.i);
            return floatAsInt.f;
        }
private:
        float be_val_;
} __attribute__((packed));

