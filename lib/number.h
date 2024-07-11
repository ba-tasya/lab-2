#pragma once
#include <cinttypes>
#include <iostream>

const short MAX_ARR_SIZE = 68; // 'cause 68 is the max number of ints to use no more than 300 bytes
const short MAX_DIGITS = 9; // 'cause int consists of 9 figures without overflow
const uint32_t MOD = 1e9;

struct uint2022_t {
    uint32_t num_by_ints[MAX_ARR_SIZE] = {0};
    int cur_int = MAX_ARR_SIZE - 1;
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
