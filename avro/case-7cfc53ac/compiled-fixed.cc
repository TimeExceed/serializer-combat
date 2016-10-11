
#include "case-fixed.hh"
#include "common/execute.hh"
#include "common/utils.hh"
#include "common/timestamp.hh"
#include <vector>
#include <string>
#include <memory>
#include <stdint.h>

using namespace std;
using namespace common;

const string kDataFilename("data/case-7cfc53ac/case.dat");

namespace common {

template<>
class SerDe<Case_7cfc53ac_Fixed>
{
public:
    void encode(const Case_7cfc53ac_Fixed& in) const
    {
        auto_ptr<avro::OutputStream> os = avro::memoryOutputStream();
        avro::EncoderPtr enc = avro::binaryEncoder();
        enc->init(*os);
        avro::encode(*enc, in);
    }

    void encode(vector<uint8_t>* out, const Case_7cfc53ac_Fixed& in) const
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
        Case_7cfc53ac_Fixed s;
        avro::DecoderPtr dec = avro::binaryDecoder();
        dec->init(*in);
        avro::decode(*dec, s);
    }
};

} // namespace common

Case_7cfc53ac_Fixed gen()
{
    vector<string> data;
    readFile(&data, kDataFilename);
    ASSERT(data.size() == 1);
    Case_7cfc53ac_Fixed res;
    toArray<1048576>(&res.bytes, data[0]);
    return res;
}

int main(int argc, char** argv) {
    common::Option opt;
    int ret = parseArgs(&opt, argc, argv);
    if (ret != 0) {
        return ret;
    }
    execute<Case_7cfc53ac_Fixed>(
        gen,
        common::SerDe<Case_7cfc53ac_Fixed>(),
        opt.encRepeat,
        opt.decRepeat);
    return 0;
}

