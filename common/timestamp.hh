#ifndef COMMON_TIMESTAMP_HH
#define COMMON_TIMESTAMP_HH

#include <stdint.h>

namespace common {

class Duration
{
    int64_t mVal;

public:
    explicit Duration(int64_t d)
      : mVal(d)
    {}

    int64_t get() const
    {
        return mVal;
    }
};

class MonotonicTime
{
    int64_t mVal;

public:
    static MonotonicTime now();

    explicit MonotonicTime(int64_t tm)
      : mVal(tm)
    {}
    
    Duration operator-(MonotonicTime ano) const
    {
        return Duration(mVal - ano.mVal);
    }
};

} // namespace common

#endif /* COMMON_TIMESTAMP_HH */
