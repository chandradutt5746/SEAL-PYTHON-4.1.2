#include <seal/modulus.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace seal;

void bind_plainmodulus(py::module &m) {
    py::class_<PlainModulus>(m, "PlainModulus")
        // Single prime for batching
        .def_static("Batching", [](std::size_t poly_modulus_degree, int bit_size) {
            return PlainModulus::Batching(poly_modulus_degree, bit_size);
        }, py::arg("poly_modulus_degree"), py::arg("bit_size"),
           "Creates a prime Modulus for batching with the given poly_modulus_degree and bit_size.")

        // Multiple primes for batching (vector<int> bit_sizes)
        .def_static("BatchingMany", [](std::size_t poly_modulus_degree, const std::vector<int> &bit_sizes) {
            return PlainModulus::Batching(poly_modulus_degree, bit_sizes);
        }, py::arg("poly_modulus_degree"), py::arg("bit_sizes"),
           "Creates several prime Modulus elements for batching with the given poly_modulus_degree and bit_sizes.");
}