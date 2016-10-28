#include "utils.hh"
#include <deque>
#include <fstream>

using namespace std;

namespace common {

int64_t atoi(const string& s)
{
    int64_t res = 0;
    for(string::const_iterator c = s.begin(); c != s.end(); ++c) {
        res *= 10;
        res += *c - '0';
    }
    return res;
}

void toVector(std::vector<uint8_t>* out, const std::string& in)
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
        out->push_back(x);
    }
}

string toString(int64_t x)
{
    bool negative = (x < 0);
    if (negative) {
        x = -x;
    }
    deque<int> segs;
    for(; x > 0; x /= 1000) {
        segs.push_front(x % 1000);
    }
    if (segs.empty()) {
        return "0";
    }
    string res;
    if (negative) {
        res.push_back('-');
    }
    {
        int x = segs.front();
        if (x / 100 > 0) {
            res.push_back('0' + (x / 100));
            x %= 100;
            res.push_back('0' + (x / 10));
            x %= 10;
            res.push_back('0' + x);
        } else if (x / 10 > 0) {
            res.push_back('0' + (x / 10));
            x %= 10;
            res.push_back('0' + x);
        } else {
            res.push_back('0' + x);
        }
        segs.pop_front();
    }
    for(; !segs.empty(); segs.pop_front()) {
        res.push_back(',');
        int x = segs.front();
        res.push_back('0' + (x / 100));
        x %= 100;
        res.push_back('0' + (x / 10));
        x %= 10;
        res.push_back('0' + x);
    }
    return res;
}

void readFile(vector<string>* out, const string& filename)
{
    ifstream fin(filename.c_str());
    string x;
    for(;;) {
        x.clear();
        fin >> x;
        if (!fin) {
            break;
        }
        out->push_back(x);
    }
}

} // namespace common
