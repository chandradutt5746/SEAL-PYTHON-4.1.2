// bind_batchencoder.cpp
#include <seal/batchencoder.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace seal;

void bind_batchencoder(py::module &m) {
    py::class_<BatchEncoder>(m, "BatchEncoder")
        .def(py::init<const SEALContext &>(), py::arg("context"),
            "Creates a BatchEncoder for the given SEALContext (must be BFV or BGV with batching enabled).")

        // Encode unsigned
        .def("encode", [](const BatchEncoder &encoder, const std::vector<std::uint64_t> &values, Plaintext &plain) {
            encoder.encode(values, plain);
        }, py::arg("values"), py::arg("plain"),
            "Encodes a vector of uint64_t into a Plaintext.")

        // Encode signed
        .def("encode", [](const BatchEncoder &encoder, const std::vector<std::int64_t> &values, Plaintext &plain) {
            encoder.encode(values, plain);
        }, py::arg("values"), py::arg("plain"),
            "Encodes a vector of int64_t into a Plaintext.")

        // Decode unsigned
        .def("decode_uint64", [](const BatchEncoder &encoder, const Plaintext &plain) {
            std::vector<std::uint64_t> values;
            encoder.decode(plain, values);
            return values;
        }, py::arg("plain"),
            "Decodes a Plaintext into a vector of uint64_t.")

        // Decode signed
        .def("decode_int64", [](const BatchEncoder &encoder, const Plaintext &plain) {
            std::vector<std::int64_t> values;
            encoder.decode(plain, values);
            return values;
        }, py::arg("plain"),
            "Decodes a Plaintext into a vector of int64_t.")

        // Slot count
        .def("slot_count", &BatchEncoder::slot_count,
            "Returns the number of batching slots (poly_modulus_degree).")

        // For BatchEncoder
        .def("encode_new", [](const BatchEncoder &encoder, const std::vector<std::uint64_t> &values) {
            Plaintext plain;
            encoder.encode(values, plain);
            return plain;
        });
}
