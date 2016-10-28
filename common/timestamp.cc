#include "timestamp.hh"
#include "common/utils.hh"
extern "C" {
#include <time.h>
}

namespace common {

MonotonicTime MonotonicTime::now()
{
    timespec tp;
    int ret = clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    ASSERT(ret == 0);
    int64_t res = tp.tv_sec;
    res *= 1000000000;
    res += tp.tv_nsec;
    return MonotonicTime(res);
}

} // namespace common

