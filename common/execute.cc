#include "execute.hh"
#include "common/utils.hh"
#include <string>

using namespace std;

namespace common {

void showEncode(const Duration& duration, int64_t repeat)
{
    printf("encode: %s ns in total %s ns per encode\n",
        toString(duration.get()).c_str(),
        toString(duration.get() / repeat).c_str());
}

void showSize(const vector<uint8_t>& buf)
{
    printf("size: %s bytes\n",
        toString(buf.size()).c_str());
}

void showDecode(const Duration& duration, int64_t repeat)
{
    printf("decode: %s ns in total %s ns per decode\n",
        toString(duration.get()).c_str(),
        toString(duration.get() / repeat).c_str());
}

int parseArgs(Option* opt, int argc, char** argv)
{
    vector<string> args;
    for(int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    FOREACH_ITER(i, args) {
        if (*i == "-h" || *i == "--help") {
            printf("Usage: exe ENCODE_REPEAT DECODE_REPEAT\n");
            return 1;
        }
    }
    if (args.size() < 2) {
        printf("Usage: exe ENCODE_REPEAT DECODE_REPEAT\n");
        return 1;
    }
    opt->encRepeat = atoi(args[0]);
    opt->decRepeat = atoi(args[1]);
    return 0;
}

} // namespace common
