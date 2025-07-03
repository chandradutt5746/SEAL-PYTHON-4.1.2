// bind_modulus.cpp
// #pragma once
#include <seal/modulus.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <fstream>

namespace py = pybind11;
using namespace seal;

void bind_modulus(py::module &m) {
    py::class_<Modulus>(m, "Modulus")
        // Constructors
        .def(py::init<>())
        .def(py::init<std::uint64_t>(), py::arg("value"))

        // Value and properties
        .def("value", &Modulus::value, "Returns the value of the modulus.")
        .def("is_zero", &Modulus::is_zero, "Returns True if the modulus is zero.")
        .def("is_prime", &Modulus::is_prime, "Returns True if the modulus is prime.")
        .def("bit_count", &Modulus::bit_count, "Returns the bit count of the modulus.")
        .def("uint64_count", &Modulus::uint64_count, "Returns the uint64 count of the modulus.")

        // Serialization
        .def("save", [](const Modulus &self, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file: " + path);
            self.save(out);
            if (!out.good()) throw std::runtime_error("Failed to write to file: " + path);
        }, py::arg("path"),
            "Saves the Modulus to a file.")

        .def("load", [](Modulus &self, const std::string &path) {
            std::ifstream in(path, std::ios::binary);
            if (!in) throw std::runtime_error("Failed to open file: " + path);
            self.load(in);
            in.close();
        }, py::arg("path"),
            "Loads the Modulus from a file.")

        // Comparison
        .def("__eq__", [](const Modulus &a, const Modulus &b) { return a == b; })
        .def("__ne__", [](const Modulus &a, const Modulus &b) { return a != b; })
        ;
    
}