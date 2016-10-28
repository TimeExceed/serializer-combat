#ifndef COMMON_UTILS_HH
#define COMMON_UTILS_HH

#include "boost/array.hpp"
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include <stdint.h>

#define FOREACH_ITER(i, coll) \
    for(typeof((coll).begin()) i = (coll).begin(); i != (coll).end(); ++i)

#define ASSERT(exp) \
    do { \
        if (!(exp)) { \
            ::std::abort(); \
        } \
    } while(false)

namespace common {

int64_t atoi(const std::string&);

template<int N>
void toArray(boost::array<uint8_t, N>* out, const std::string& in)
{
    ASSERT(in.size() % 2 == 0);
    for(int64_t i = 0, sz = in.size() / 2; i < sz; ++i) {
        uint8_t x = 0;
        char c = in[i * 2];
        if ('0' <= c && c <= '9') {
            x += c - '0';
        } else {
            x += c - 'A';
        }
        x <<= 4;
        c = in[i * 2 + 1];
        if ('0' <= c && c <= '9') {
            x += c - '0';
        } else {
            x += c - 'A';
        }
        out->at(i) = x;
    }
}

void toVector(std::vector<uint8_t>* out, const std::string& in);

std::string toString(int64_t);

void readFile(std::vector<std::string>*, const std::string& filename);

} // namespace common


#endif /* COMMON_UTILS_HH */
