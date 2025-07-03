#include <seal/modulus.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace seal;

void bind_coeffmodulus(py::module &m) {
    py::class_<CoeffModulus>(m, "CoeffModulus")
        // Returns a default coefficient modulus for BFV at a given security level
        .def_static("BFVDefault", [](std::size_t poly_modulus_degree, sec_level_type sec_level = sec_level_type::tc128) {
            return CoeffModulus::BFVDefault(poly_modulus_degree, sec_level);
        }, py::arg("poly_modulus_degree"), py::arg("sec_level") = sec_level_type::tc128,
           "Returns a default coefficient modulus for BFV at the given security level.")

        // Returns a custom coefficient modulus for CKKS/BFV/BGV
        .def_static("Create", [](std::size_t poly_modulus_degree, const std::vector<int> &bit_sizes) {
            return CoeffModulus::Create(poly_modulus_degree, bit_sizes);
        }, py::arg("poly_modulus_degree"), py::arg("bit_sizes"),
           "Creates a custom coefficient modulus with the given bit sizes.")

        // Returns a custom coefficient modulus with a plain modulus (for BGV)
        .def_static("CreateWithPlainModulus", [](std::size_t poly_modulus_degree, const Modulus &plain_modulus, const std::vector<int> &bit_sizes) {
            return CoeffModulus::Create(poly_modulus_degree, plain_modulus, bit_sizes);
        }, py::arg("poly_modulus_degree"), py::arg("plain_modulus"), py::arg("bit_sizes"),
           "Creates a custom coefficient modulus with a plain modulus (for BGV).")

        // Returns the maximum bit count for a given poly_modulus_degree and security level
        .def_static("MaxBitCount", [](std::size_t poly_modulus_degree, sec_level_type sec_level = sec_level_type::tc128) {
            return CoeffModulus::MaxBitCount(poly_modulus_degree, sec_level);
        }, py::arg("poly_modulus_degree"), py::arg("sec_level") = sec_level_type::tc128,
           "Returns the maximum bit count for the given poly_modulus_degree and security level.");
}