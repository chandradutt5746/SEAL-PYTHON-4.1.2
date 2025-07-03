#include "bind_ciphertext.h"
#include <seal/ciphertext.h>
#include <pybind11/pybind11.h>
#include <fstream>

namespace py = pybind11;
using namespace seal;

void bind_ciphertext(py::module &m) {
    py::class_<Ciphertext>(m, "Ciphertext")
        .def(py::init<>())
        .def(py::init<const SEALContext&>())
        .def("parms_id", [](const Ciphertext &ct) {
            auto id = ct.parms_id();
            return py::bytes(reinterpret_cast<const char*>(id.data()), id.size());
        })
        .def("scale", py::overload_cast<>(&Ciphertext::scale, py::const_))
        .def("set_scale", [](Ciphertext &ct, double scale) { ct.scale() = scale; })
        .def("size", &Ciphertext::size)
        .def("size_capacity", &Ciphertext::size_capacity)
        .def("poly_modulus_degree", &Ciphertext::poly_modulus_degree)
        .def("coeff_modulus_size", &Ciphertext::coeff_modulus_size)
        .def("is_ntt_form", py::overload_cast<>(&Ciphertext::is_ntt_form, py::const_))
        .def("is_transparent", py::overload_cast<>(&Ciphertext::is_transparent, py::const_))
        .def("correction_factor", py::overload_cast<>(&Ciphertext::correction_factor, py::const_))
        .def("set_correction_factor", [](Ciphertext &ct, std::uint64_t cf) { ct.correction_factor() = cf; })
        .def("reserve", py::overload_cast<std::size_t>(&Ciphertext::reserve))
        .def("reserve_with_context", [](Ciphertext &ct, const SEALContext &ctx, std::size_t size) {
            ct.reserve(ctx, size);
        })
        .def("release", &Ciphertext::release)
        .def("save", [](const Ciphertext &self, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file for writing");
            self.save(out);
            out.close();
        })
        .def("load", [](Ciphertext &self, const SEALContext &context, const std::string &path) {
            std::ifstream in(path, std::ios::binary);
            if (!in) throw std::runtime_error("Failed to open file for reading");
            self.load(context, in);
            in.close();
        })
        .def("resize", [](Ciphertext &ct, std::size_t size) { ct.resize(size); })
        ;
}