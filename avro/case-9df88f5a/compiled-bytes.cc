
#include "case-bytes.hh"
#include "common/execute.hh"
#include "common/utils.hh"
#include "common/timestamp.hh"
#include <vector>
#include <string>
#include <memory>
#include <stdint.h>

using namespace std;
using namespace common;

const string kDataFilename("data/case-9df88f5a/case.dat");

namespace common {

template<>
class SerDe<Case_9df88f5a_Bytes>
{
public:
    void encode(const Case_9df88f5a_Bytes& in) const
    {
        auto_ptr<avro::OutputStream> os = avro::memoryOutputStream();
        avro::EncoderPtr enc = avro::binaryEncoder();
        enc->init(*os);
        avro::encode(*enc, in);
    }

    void encode(vector<uint8_t>* out, const Case_9df88f5a_Bytes& in) const
    {
        auto_ptr<avro::OutputStream> os = avro::memoryOutputStream();
        avro::EncoderPtr enc = avro::binaryEncoder();
        enc->init(*os);
        avro::encode(*enc, in);
        boost::shared_ptr<std::vector<uint8_t> > buf = avro::snapshot(*os);
        std::swap(*out, *buf);
    }

    void decode(const vector<uint8_t>& buf) const
    {
        auto_ptr<avro::InputStream> in = avro::memoryInputStream(buf.data(), buf.size());
        Case_9df88f5a_Bytes s;
        avro::DecoderPtr dec = avro::binaryDecoder();
        dec->init(*in);
        avro::decode(*dec, s);
    }
};

} // namespace common

Case_9df88f5a_Bytes gen()
{
    vector<string> data;
    readFile(&data, kDataFilename);
    Case_9df88f5a_Bytes res;
    FOREACH_ITER(i, data) {
        vector<uint8_t> x;
        toVector(&x, *i);
        res.bytes.push_back(x);
    }
    return res;
}

int main(int argc, char** argv) {
    common::Option opt;
    int ret = parseArgs(&opt, argc, argv);
    if (ret != 0) {
        return ret;
    }
    execute<Case_9df88f5a_Bytes>(
        gen,
        common::SerDe<Case_9df88f5a_Bytes>(),
        opt.encRepeat,
        opt.decRepeat);
    return 0;
}

