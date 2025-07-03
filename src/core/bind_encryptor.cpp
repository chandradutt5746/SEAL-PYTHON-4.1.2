#include "bind_encryptor.h"
#include <seal/encryptor.h>
#include <seal/serializable.h>
#include <pybind11/pybind11.h>
#include <fstream>
#include <vector>

namespace py = pybind11;
using namespace seal;

void bind_encryptor(py::module &m) {
    py::class_<Encryptor>(m, "Encryptor")
        // Constructors
        .def(py::init<const SEALContext&, const PublicKey&>(), py::arg("context"), py::arg("public_key"))
        .def(py::init<const SEALContext&, const SecretKey&>(), py::arg("context"), py::arg("secret_key"))
        .def(py::init<const SEALContext&, const PublicKey&, const SecretKey&>(), py::arg("context"), py::arg("public_key"), py::arg("secret_key"))

        // Encrypt (returns Serializable<Ciphertext>)
        .def("encrypt", [](Encryptor &self, const Plaintext &plain) {
            return self.encrypt(plain);
        }, py::arg("plain"),
            "Encrypts a Plaintext and returns a SerializableCiphertext.")

        // Encrypt (in-place, writes to Ciphertext)
        .def("encrypt_inplace", [](Encryptor &self, const Plaintext &plain, Ciphertext &cipher) {
            self.encrypt(plain, cipher);
        }, py::arg("plain"), py::arg("cipher"),
            "Encrypts a Plaintext and writes to a Ciphertext (in-place).")

        // Encrypt zero (returns Serializable<Ciphertext>)
        .def("encrypt_zero", [](Encryptor &self) {
            return self.encrypt_zero();
        }, "Encrypts zero and returns a SerializableCiphertext.")

        .def("encrypt_zero_with_parms_id", [](Encryptor &self, parms_id_type parms_id) {
            return self.encrypt_zero(parms_id);
        }, py::arg("parms_id"),
            "Encrypts zero at a specific parms_id and returns a SerializableCiphertext.")

        // Encrypt zero (in-place)
        .def("encrypt_zero_inplace", [](Encryptor &self, Ciphertext &cipher) {
            self.encrypt_zero(cipher);
        }, py::arg("cipher"),
            "Encrypts zero and writes to a Ciphertext (in-place).")

        .def("encrypt_zero_inplace_with_parms_id", [](Encryptor &self, parms_id_type parms_id, Ciphertext &cipher) {
            self.encrypt_zero(parms_id, cipher);
        }, py::arg("parms_id"), py::arg("cipher"),
            "Encrypts zero at a specific parms_id and writes to a Ciphertext (in-place).")

        // Symmetric encryption (returns Serializable<Ciphertext>)
        .def("encrypt_symmetric", [](Encryptor &self, const Plaintext &plain) {
            return self.encrypt_symmetric(plain);
        }, py::arg("plain"),
            "Encrypts a Plaintext using symmetric encryption and returns a SerializableCiphertext.")

        // Symmetric encryption (in-place)
        .def("encrypt_symmetric_inplace", [](Encryptor &self, const Plaintext &plain, Ciphertext &cipher) {
            self.encrypt_symmetric(plain, cipher);
        }, py::arg("plain"), py::arg("cipher"),
            "Encrypts a Plaintext using symmetric encryption and writes to a Ciphertext (in-place).")

        // Symmetric encrypt zero (returns Serializable<Ciphertext>)
        .def("encrypt_zero_symmetric", [](Encryptor &self) {
            return self.encrypt_zero_symmetric();
        }, "Encrypts zero using symmetric encryption and returns a SerializableCiphertext.")

        .def("encrypt_zero_symmetric_with_parms_id", [](Encryptor &self, parms_id_type parms_id) {
            return self.encrypt_zero_symmetric(parms_id);
        }, py::arg("parms_id"),
            "Encrypts zero at a specific parms_id using symmetric encryption and returns a SerializableCiphertext.")

        // Symmetric encrypt zero (in-place)
        .def("encrypt_zero_symmetric_inplace", [](Encryptor &self, Ciphertext &cipher) {
            self.encrypt_zero_symmetric(cipher);
        }, py::arg("cipher"),
            "Encrypts zero using symmetric encryption and writes to a Ciphertext (in-place).")

        .def("encrypt_zero_symmetric_inplace_with_parms_id", [](Encryptor &self, parms_id_type parms_id, Ciphertext &cipher) {
            self.encrypt_zero_symmetric(parms_id, cipher);
        }, py::arg("parms_id"), py::arg("cipher"),
            "Encrypts zero at a specific parms_id using symmetric encryption and writes to a Ciphertext (in-place).")
        ;
    

    py::class_<Serializable<Ciphertext>>(m, "SerializableCiphertext")
        .def("save", [](const Serializable<Ciphertext> &self, const std::string &path) {
                std::ofstream out(path, std::ios::binary);
                if (!out) throw std::runtime_error("Failed to open file: " + path);
                self.save(out);
                if (!out.good()) throw std::runtime_error("Failed to write to file: " + path);
            }, py::arg("path"),
                "Saves the SerializableCiphertext to a file.");
}