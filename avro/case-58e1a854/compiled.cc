
#include "case.hh"
#include "common/execute.hh"
#include "common/utils.hh"
#include "common/timestamp.hh"
#include <vector>
#include <string>
#include <memory>
#include <stdint.h>

using namespace std;
using namespace common;

const string kDataFilename("data/case-58e1a854/case.dat");

namespace common {

template<>
class SerDe<Case_58e1a854>
{
public:
    void encode(const Case_58e1a854& in) const
    {
        auto_ptr<avro::OutputStream> os = avro::memoryOutputStream();
        avro::EncoderPtr enc = avro::binaryEncoder();
        enc->init(*os);
        avro::encode(*enc, in);
    }

    void encode(vector<uint8_t>* out, const Case_58e1a854& in) const
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
        Case_58e1a854 s;
        avro::DecoderPtr dec = avro::binaryDecoder();
        dec->init(*in);
        avro::decode(*dec, s);
    }
};

} // namespace common

Case_58e1a854 gen()
{
    vector<string> data;
    readFile(&data, kDataFilename);
    ASSERT(data.size() == 1);
    Case_58e1a854 res;
    res.str = data[0];
    return res;
}

int main(int argc, char** argv) {
    common::Option opt;
    int ret = parseArgs(&opt, argc, argv);
    if (ret != 0) {
        return ret;
    }
    execute<Case_58e1a854>(
        gen,
        common::SerDe<Case_58e1a854>(),
        opt.encRepeat,
        opt.decRepeat);
    return 0;
}

