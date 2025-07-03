#include <seal/evaluator.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace seal;

void bind_advanced(py::module &m) {
    // py::class_<Evaluator>(m, "Evaluator")
    //     // Add these to existing evaluator methods
    //     .def("add_plain", [](Evaluator &e, Ciphertext &a, const Plaintext &b) {
    //         e.add_plain_inplace(a, b);
    //     })
    //     .def("multiply_plain", [](Evaluator &e, Ciphertext &a, const Plaintext &b) {
    //         e.multiply_plain_inplace(a, b);
    //     })
    //     .def("rescale_to_next", [](Evaluator &e, Ciphertext &a) {
    //         e.rescale_to_next_inplace(a);
    //     })
    //     .def("complex_conjugate", [](Evaluator &e, Ciphertext &a, const GaloisKeys &galois_keys) {
    //         e.complex_conjugate_inplace(a, galois_keys);
    //     });
    continue;
}