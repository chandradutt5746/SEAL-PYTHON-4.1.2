#include <seal/decryptor.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace seal;

void bind_decryptor(py::module &m) {
    py::class_<Decryptor>(m, "Decryptor")
        .def(py::init<const SEALContext&, const SecretKey&>(),
            py::arg("context"), py::arg("secret_key"),
            "Creates a Decryptor for the given SEALContext and SecretKey.")

        // In-place decrypt (official API)
        .def("decrypt", [](Decryptor &self, const Ciphertext &encrypted, Plaintext &destination) {
            self.decrypt(encrypted, destination);
        }, py::arg("encrypted"), py::arg("destination"),
            "Decrypts a Ciphertext into a Plaintext (in-place).")

        // Optional: out-of-place decrypt for Pythonic usage
        .def("decrypt_new", [](Decryptor &self, const Ciphertext &encrypted) {
            Plaintext destination;
            self.decrypt(encrypted, destination);
            return destination;
        }, py::arg("encrypted"),
            "Decrypts a Ciphertext and returns a new Plaintext.")

        // Invariant noise budget
        .def("invariant_noise_budget", &Decryptor::invariant_noise_budget,
            py::arg("encrypted"),
            "Returns the invariant noise budget of a Ciphertext.");
}