#include "number.h"
#include <iomanip>

uint2022_t from_uint(uint32_t x) {
    uint2022_t number;
    
    number.num_by_ints[number.cur_int] = x % MOD;
    number.num_by_ints[number.cur_int - 1] = x / MOD;
    if (x / MOD != 0) {
        number.cur_int--;
    }
    
    return number;
}

uint2022_t from_string(const char* str) {
    uint2022_t number;
    
    uint32_t len = 0;
    while (str[++len]) {
    }
    if (len == 0) {
        return number;
    }

    uint32_t cnt_ints = (len - 1) / MAX_DIGITS + 1;
    if (cnt_ints > MAX_ARR_SIZE) {
        std::cerr << "undefined behaviour";
        exit(EXIT_FAILURE);
    }
    number.cur_int = MAX_ARR_SIZE - cnt_ints;
    
    uint32_t first_int_size = len - cnt_ints * MAX_DIGITS + MAX_DIGITS;
    uint32_t max_first_int = 1;
    for (uint32_t i = 1; i < first_int_size; i++) {
        max_first_int *= 10;
    }
    
    uint32_t cur_num_int = number.cur_int;
    uint32_t cur_int_size = 0;
    uint32_t to_num;
    bool is_first_filled;
    for (uint32_t i = 0; i < len; i++) {
        int to_num = str[i] - static_cast<uint32_t>('0');
        cur_int_size++;
        number.num_by_ints[cur_num_int] = number.num_by_ints[cur_num_int] * 10 + to_num;
        
        is_first_filled = (cur_int_size == first_int_size) && (i < cur_int_size);
        if ((cur_int_size == MAX_DIGITS) || is_first_filled) {
            cur_int_size = 0;
            cur_num_int++;
        }
    }
    
    return number;
}

bool operator<(const uint2022_t& num1, const uint2022_t& num2) {
    if (num1.cur_int != num2.cur_int) {
        return num1.cur_int > num2.cur_int;
    }
    for (uint32_t i = num1.cur_int; i < MAX_ARR_SIZE; i++) {
        if (num1.num_by_ints[i] != num2.num_by_ints[i]) {
            return num1.num_by_ints[i] < num2.num_by_ints[i];
        }
    }
    
    return false;
}

bool operator>(const uint2022_t& num1, const uint2022_t& num2) {
    return num2 < num1;
}

bool operator==(const uint2022_t& num1, const uint2022_t& num2) {
    if (num1.cur_int != num2.cur_int) {
        return false;
    }
    for (uint32_t i = num1.cur_int; i < MAX_ARR_SIZE; i++) {
        if (num1.num_by_ints[i] != num2.num_by_ints[i]) {
            return false;
        }
    }
    
    return true;
}

bool operator<=(const uint2022_t& num1, const uint2022_t& num2) {
    return (num1 < num2) || (num1 == num2);
}

bool operator>=(const uint2022_t& num1, const uint2022_t& num2) {
    return (num1 > num2) || (num1 == num2);
}

bool operator!=(const uint2022_t& num1, const uint2022_t& num2) {
    return !(num1 == num2);
}

uint2022_t operator+(const uint2022_t& sum1, const uint2022_t& sum2) {
    uint2022_t sum;
    
    bool in_mind = false;
    uint32_t min_cur_int = std::min(sum1.cur_int, sum2.cur_int);
    uint32_t cur_sum;
    for (uint32_t i = MAX_ARR_SIZE - 1; i >= min_cur_int; i--) {
        cur_sum = sum1.num_by_ints[i] + sum2.num_by_ints[i] + static_cast<uint32_t>(in_mind);
        sum.num_by_ints[sum.cur_int] = cur_sum % MOD;
        sum.cur_int--;
        in_mind = (cur_sum < MOD ? 0 : 1);
    }
    sum.num_by_ints[sum.cur_int] += in_mind;
    if (sum.num_by_ints[sum.cur_int] == 0)
    {
        sum.cur_int++;
    }
    
    return sum;
}

uint2022_t operator-(const uint2022_t& reduce, const uint2022_t& deduct) {
    uint2022_t diff;
    
    if (reduce < deduct) {
        std::cerr << "undefined behaviour";
        exit(EXIT_FAILURE);
    } else if (reduce == deduct) {
        return diff;
    }
    
    uint32_t cur_diff;
    bool from_mind = false;
    for (uint32_t i = MAX_ARR_SIZE - 1; i >= reduce.cur_int; i--) {
        cur_diff = reduce.num_by_ints[i] - deduct.num_by_ints[i] - static_cast<uint32_t>(from_mind);
        if (cur_diff < 0) {
            cur_diff = MOD - cur_diff;
        }
        diff.num_by_ints[i] = cur_diff;
        from_mind = (cur_diff < 0 ? 1 : 0);
    }
    
    for (uint32_t i = 0; i < MAX_ARR_SIZE; i++) {
        if (diff.num_by_ints[i] != 0) {
            diff.cur_int = i;
            break;
        }
    }
    
    return diff;
}

uint2022_t operator*(const uint2022_t& mult1, const uint2022_t& mult2) {
    uint2022_t comp;
    
    uint64_t cur_comp;
    uint32_t cur_comp_int;
    for (uint32_t i = MAX_ARR_SIZE - 1; i >= mult1.cur_int; i--) {
        for (uint32_t j = MAX_ARR_SIZE - 1; j >= mult2.cur_int; j--) {
            cur_comp = mult1.num_by_ints[i];
            cur_comp_int = i + j - MAX_ARR_SIZE + 1;
            cur_comp = cur_comp * mult2.num_by_ints[j] + comp.num_by_ints[cur_comp_int];
            if (cur_comp_int < 0 || (cur_comp_int == 0 && cur_comp >= MOD)) {
                std::cerr << "undefined behaviour";
                exit(EXIT_FAILURE);
            }
            comp.num_by_ints[cur_comp_int] = cur_comp % MOD;
            comp.num_by_ints[cur_comp_int - 1] += cur_comp / MOD;
        }
    }
    
    for (uint32_t i = 0; i < MAX_ARR_SIZE; i++) {
        if (comp.num_by_ints[i] != 0) {
            comp.cur_int = i;
            break;
        }
    }
    
    return comp;
}

uint2022_t operator/(const uint2022_t& divis, const uint2022_t& divide) {
    uint2022_t quot;
    
    if (divis < divide) {
        return quot;
    }
    
    uint2022_t numer = divis;
    uint2022_t denom;
    uint2022_t ans;
    uint2022_t type1 = from_uint(1);
    uint2022_t type10 = from_uint(10);
    while (numer >= divide) {
        denom = divide;
        ans = type1;
        while (denom + type10 <= numer) {
            denom = denom * type10;
            ans = ans * type10;
        }
        while (numer >= denom) {
            numer = numer - denom;
            quot = quot + ans;
        }
    }
    
    return quot;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& number) {
    if ((number.cur_int == MAX_ARR_SIZE - 1) || (number.num_by_ints[number.cur_int] != 0)) {
        stream << number.num_by_ints[number.cur_int];
    }
    for (uint32_t i = number.cur_int + 1; i < MAX_ARR_SIZE; i++) {
        stream << std::setfill('0') << std::setw(MAX_DIGITS) << number.num_by_ints[i];
    }
   
    return stream;
}
