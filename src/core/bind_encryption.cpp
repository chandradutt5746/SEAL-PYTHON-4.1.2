#include <seal/seal.h>
#include <seal/encryptionparams.h>
#include <seal/modulus.h>
#include <seal/randomgen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <fstream>

namespace py = pybind11;
using namespace seal;

void bind_encryption_parameters(py::module &m) {
    py::class_<EncryptionParameters>(m, "EncryptionParameters")
        // Constructors
        .def(py::init<scheme_type>(), py::arg("scheme") = scheme_type::none)
        .def(py::init<const EncryptionParameters &>(), py::arg("copy"))

        // Setters
        .def("set_poly_modulus_degree", &EncryptionParameters::set_poly_modulus_degree)
        .def("set_coeff_modulus", [](EncryptionParameters &parms, const std::vector<Modulus> &moduli) {
            parms.set_coeff_modulus(moduli);
        })
        .def("set_plain_modulus", py::overload_cast<const Modulus &>(&EncryptionParameters::set_plain_modulus))
        .def("set_plain_modulus", py::overload_cast<std::uint64_t>(&EncryptionParameters::set_plain_modulus))
        .def("set_random_generator", &EncryptionParameters::set_random_generator)

        // Getters
        .def("scheme", &EncryptionParameters::scheme)
        .def("poly_modulus_degree", &EncryptionParameters::poly_modulus_degree)
        .def("coeff_modulus", [](const EncryptionParameters &p) { return p.coeff_modulus(); })
        .def("plain_modulus", &EncryptionParameters::plain_modulus)
        .def("random_generator", &EncryptionParameters::random_generator)

        // Serialization
        .def("save", [](const EncryptionParameters &self, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file for writing");
            self.save(out);
            out.close();
        })
        .def("load", [](EncryptionParameters &self, const std::string &path) {
            std::ifstream in(path, std::ios::binary);
            if (!in) throw std::runtime_error("Failed to open file for reading");
            self.load(in);
            in.close();
        })

        // Comparison
        .def("__eq__", [](const EncryptionParameters &a, const EncryptionParameters &b) { return a == b; })
        .def("__ne__", [](const EncryptionParameters &a, const EncryptionParameters &b) { return a != b; })

        // ParmsId (as bytes)
        .def("parms_id", [](const EncryptionParameters &p) {
            auto id = p.parms_id();
            return py::bytes(reinterpret_cast<const char*>(id.data()), id.size());
        });
}