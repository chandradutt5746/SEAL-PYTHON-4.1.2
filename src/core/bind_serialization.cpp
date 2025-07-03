#include "bind_serialization.h"
#include <seal/serialization.h>
#include <seal/serializable.h>
#include <seal/publickey.h>
#include <seal/secretkey.h>
#include <seal/relinkeys.h>
#include <seal/galoiskeys.h>
#include <seal/ciphertext.h>
#include <seal/plaintext.h>
#include <seal/context.h>
#include <fstream>
#include <pybind11/pybind11.h>


namespace py = pybind11;
using namespace seal;

void bind_serialization(py::module &m) {
    // Save for specific types
    m.def("save", [](const PublicKey &obj, const std::string &path) {
        std::ofstream out(path, std::ios::binary);
        if (!out.is_open()) throw std::runtime_error("Cannot open file: " + path);
        obj.save(out);
    }, py::arg("obj"), py::arg("path"));

    m.def("save", [](const SecretKey &obj, const std::string &path) {
        std::ofstream out(path, std::ios::binary);
        if (!out.is_open()) throw std::runtime_error("Cannot open file: " + path);
        obj.save(out);
    }, py::arg("obj"), py::arg("path"));

    m.def("save", [](const RelinKeys &obj, const std::string &path) {
        std::ofstream out(path, std::ios::binary);
        if (!out.is_open()) throw std::runtime_error("Cannot open file: " + path);
        obj.save(out);
    }, py::arg("obj"), py::arg("path"));

    m.def("save", [](const GaloisKeys &obj, const std::string &path) {
        std::ofstream out(path, std::ios::binary);
        if (!out.is_open()) throw std::runtime_error("Cannot open file: " + path);
        obj.save(out);
    }, py::arg("obj"), py::arg("path"));

    m.def("save", [](const Ciphertext &obj, const std::string &path) {
        std::ofstream out(path, std::ios::binary);
        if (!out.is_open()) throw std::runtime_error("Cannot open file: " + path);
        obj.save(out);
    }, py::arg("obj"), py::arg("path"));

    m.def("save", [](const Plaintext &obj, const std::string &path) {
        std::ofstream out(path, std::ios::binary);
        if (!out.is_open()) throw std::runtime_error("Cannot open file: " + path);
        obj.save(out);
    }, py::arg("obj"), py::arg("path"));

    // Load public key
    m.def("load_public_key", [](const SEALContext &context, const std::string &path) {
        std::ifstream in(path, std::ios::binary);
        if (!in.is_open()) throw std::runtime_error("Cannot open file: " + path);
        PublicKey key;
        key.load(context, in);
        return key;
    }, py::arg("context"), py::arg("path"));

    // Load secret key
    m.def("load_secret_key", [](const SEALContext &context, const std::string &path) {
        std::ifstream in(path, std::ios::binary);
        if (!in.is_open()) throw std::runtime_error("Cannot open file: " + path);
        SecretKey key;
        key.load(context, in);
        return key;
    }, py::arg("context"), py::arg("path"));

    // Load relinearization keys
    m.def("load_relin_keys", [](const SEALContext &context, const std::string &path) {
        std::ifstream in(path, std::ios::binary);
        if (!in.is_open()) throw std::runtime_error("Cannot open file: " + path);
        RelinKeys keys;
        keys.load(context, in);
        return keys;
    }, py::arg("context"), py::arg("path"));

    // Load Galois keys
    m.def("load_galois_keys", [](const SEALContext &context, const std::string &path) {
        std::ifstream in(path, std::ios::binary);
        if (!in.is_open()) throw std::runtime_error("Cannot open file: " + path);
        GaloisKeys keys;
        keys.load(context, in);
        return keys;
    }, py::arg("context"), py::arg("path"));

    // Load ciphertext
    m.def("load_ciphertext", [](const SEALContext &context, const std::string &path) {
        std::ifstream in(path, std::ios::binary);
        if (!in.is_open()) throw std::runtime_error("Cannot open file: " + path);
        Ciphertext ct;
        ct.load(context, in);
        return ct;
    }, py::arg("context"), py::arg("path"));

    // Load plaintext
    m.def("load_plaintext", [](const SEALContext &context, const std::string &path) {
        std::ifstream in(path, std::ios::binary);
        if (!in.is_open()) throw std::runtime_error("Cannot open file: " + path);
        Plaintext pt;
        pt.load(context, in);
        return pt;
    }, py::arg("context"), py::arg("path"));
}