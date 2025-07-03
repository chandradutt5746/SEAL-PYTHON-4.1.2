
#include "bind_plaintext.h"
#include <seal/plaintext.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <fstream>

namespace py = pybind11;
using namespace seal;

void bind_plaintext(py::module &m) {
    py::class_<Plaintext>(m, "Plaintext")
        // Constructors
        .def(py::init<>())
        .def(py::init<const std::string &>(), py::arg("hex_poly"))
        .def(py::init<std::size_t>(), py::arg("coeff_count"))
        .def(py::init<const Plaintext &>(), py::arg("copy"))

        // String representation
        .def("to_string", &Plaintext::to_string)

        // Data access as memoryview
        .def("data", [](Plaintext &pt) {
            return py::memoryview::from_buffer(
                pt.data(),
                {static_cast<py::ssize_t>(pt.coeff_count())},
                {sizeof(Plaintext::pt_coeff_type)}
            );
        }, py::keep_alive<0, 1>())

        // Properties
        .def("coeff_count", &Plaintext::coeff_count)
        .def("capacity", &Plaintext::capacity)
        .def("significant_coeff_count", &Plaintext::significant_coeff_count)
        .def("nonzero_coeff_count", &Plaintext::nonzero_coeff_count)
        .def("is_zero", &Plaintext::is_zero)
        .def("is_ntt_form", &Plaintext::is_ntt_form)
        .def("parms_id", [](const Plaintext &pt) {
            auto id = pt.parms_id();
            return py::bytes(reinterpret_cast<const char*>(id.data()), id.size());
        })
        .def("scale", py::overload_cast<>(&Plaintext::scale, py::const_))
        .def("set_scale", [](Plaintext &pt, double scale) { pt.scale() = scale; })

        // Resize, reserve, shrink, release
        .def("resize", &Plaintext::resize)
        .def("reserve", &Plaintext::reserve)
        .def("shrink_to_fit", &Plaintext::shrink_to_fit)
        .def("release", &Plaintext::release)

        // Zeroing
        .def("set_zero", py::overload_cast<>(&Plaintext::set_zero))
        .def("set_zero_range", [](Plaintext &pt, std::size_t start, std::size_t length) { pt.set_zero(start, length); })
        .def("set_zero_from", [](Plaintext &pt, std::size_t start) { pt.set_zero(start); })

        // Assignment from string or constant
        .def("assign", [](Plaintext &pt, const std::string &hex_poly) { pt = hex_poly; })
        .def("assign_const", [](Plaintext &pt, Plaintext::pt_coeff_type value) { pt = value; })

        // Serialization
        .def("save", [](const Plaintext &self, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file: " + path);
            self.save(out);
            if (!out.good()) throw std::runtime_error("Failed to write to file: " + path);
        }, py::arg("path"),
            "Saves the Plaintext to a file.")

        .def("load", [](Plaintext &self, const SEALContext &context, const std::string &path) {
            std::ifstream in(path, std::ios::binary);
            if (!in) throw std::runtime_error("Failed to open file: " + path);
            self.load(context, in);
            in.close();
        }, py::arg("context"), py::arg("path"),
            "Loads the Plaintext from a file with the given SEALContext.")

        // Comparison
        .def("__eq__", [](const Plaintext &a, const Plaintext &b) { return a == b; })
        .def("__ne__", [](const Plaintext &a, const Plaintext &b) { return a != b; })
        ;
}