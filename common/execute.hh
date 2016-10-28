#ifndef COMMON_EXECUTE_HH
#define COMMON_EXECUTE_HH

#include "common/timestamp.hh"
#include <tr1/functional>
#include <vector>
#include <stdint.h>

namespace common {

template<typename T>
class SerDe
{
public:
    // void encode(const T&) const;
    // void encode(std::vector<uint8_t>*, const T&) const;
    // void decode(const std::vector<uint8_t>&) const;
};

void showEncode(const Duration&, int64_t repeat);
void showSize(const std::vector<uint8_t>&);
void showDecode(const Duration&, int64_t repeat);

template<typename T>
void execute(
    const std::tr1::function<T()>& gen,
    const SerDe<T>& serde,
    int64_t encRepeat,
    int64_t decRepeat)
{
    T cs = gen();
    {
        MonotonicTime start = MonotonicTime::now();
        for(int64_t i = 0; i < encRepeat; ++i) {
            serde.encode(cs);
        }
        Duration d = MonotonicTime::now() - start;
        showEncode(d, encRepeat);
    }
    std::vector<uint8_t> buf;
    serde.encode(&buf, cs);
    showSize(buf);
    {
        MonotonicTime start = MonotonicTime::now();
        for(int64_t i = 0; i < decRepeat; ++i) {
            serde.decode(buf);
        }
        Duration d = MonotonicTime::now() - start;
        showDecode(d, decRepeat);
    }
}

struct Option
{
    int64_t encRepeat;
    int64_t decRepeat;

    Option()
      : encRepeat(0),
        decRepeat(0)
    {}
};

int parseArgs(Option* opt, int argc, char** argv);

} // namespace common

#endif /* COMMON_EXECUTE_HH */
