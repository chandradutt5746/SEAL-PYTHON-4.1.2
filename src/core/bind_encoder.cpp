#include <seal/seal.h>
#include <seal/batchencoder.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;
using namespace seal;

void bind_encoder(py::module &m) {
    py::class_<BatchEncoder>(m, "BatchEncoder")
        .def(py::init<const SEALContext &>())
        .def("encode", [](const BatchEncoder &encoder, const std::vector<std::uint64_t> &values) {
            Plaintext plain;
            encoder.encode(values, plain);
            return plain;
        })
        .def("encode", [](const BatchEncoder &encoder, const std::vector<std::int64_t> &values) {
            Plaintext plain;
            encoder.encode(values, plain);
            return plain;
        })
        .def("decode_uint64", [](const BatchEncoder &encoder, const Plaintext &plain) {
            std::vector<std::uint64_t> values;
            encoder.decode(plain, values);
            return values;
        })
        .def("decode_int64", [](const BatchEncoder &encoder, const Plaintext &plain) {
            std::vector<std::int64_t> values;
            encoder.decode(plain, values);
            return values;
        })
        .def("slot_count", &BatchEncoder::slot_count);
}