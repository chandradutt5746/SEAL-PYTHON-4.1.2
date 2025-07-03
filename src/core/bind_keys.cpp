#include "bind_keys.h"
#include <seal/keygenerator.h>
#include <seal/publickey.h>
#include <seal/secretkey.h>
#include <seal/relinkeys.h>
#include <seal/galoiskeys.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <fstream>
#include <vector>

namespace py = pybind11;
using namespace seal;

void bind_keys(py::module &m) {
    py::class_<PublicKey>(m, "PublicKey")
        .def(py::init<>())
        .def("data", [](const PublicKey &key) {
            return key.data();
        })
        .def("save", [](const PublicKey &obj, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file: " + path);
            obj.save(out);
            if (!out.good()) throw std::runtime_error("Failed to write to file: " + path);
        });

    py::class_<SecretKey>(m, "SecretKey")
        .def(py::init<>())
        .def("data", [](const SecretKey &key) {
            return key.data();
        })
        .def("save", [](const SecretKey &obj, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file: " + path);
            obj.save(out);
            if (!out.good()) throw std::runtime_error("Failed to write to file: " + path);
        });

    py::class_<RelinKeys>(m, "RelinKeys")
        .def(py::init<>())
        .def("save", [](const RelinKeys &obj, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file: " + path);
            obj.save(out);
            if (!out.good()) throw std::runtime_error("Failed to write to file: " + path);
        });

    py::class_<GaloisKeys>(m, "GaloisKeys")
        .def(py::init<>())
        .def("save", [](const GaloisKeys &obj, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file: " + path);
            obj.save(out);
            if (!out.good()) throw std::runtime_error("Failed to write to file: " + path);
        });

    // Bind KeyGenerator with correct method names for SEAL 4.1.2
    py::class_<KeyGenerator>(m, "KeyGenerator")
        // Constructors
        .def(py::init<const SEALContext &>(), py::arg("context"))
        .def(py::init<const SEALContext &, const SecretKey &>(), py::arg("context"), py::arg("secret_key"))

        // Public key
        .def("create_public_key", [](KeyGenerator &kg) {
            PublicKey pk;
            kg.create_public_key(pk);
            return pk;
        }, "Generates a new public key and returns it.")

        // Secret key
        .def("secret_key", &KeyGenerator::secret_key, py::return_value_policy::reference_internal,
            "Returns the secret key.")

        // Relinearization keys (default count = 1)
        .def("create_relin_keys", [](KeyGenerator &kg) {
            RelinKeys rk;
            kg.create_relin_keys(rk);
            return rk;
        })

        // Galois keys (all)
        .def("create_galois_keys", [](KeyGenerator &kg) {
            GaloisKeys gk;
            kg.create_galois_keys(gk);
            return gk;
        }, "Generates all Galois keys and returns them.");
}