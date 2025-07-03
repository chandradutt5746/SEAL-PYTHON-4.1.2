#include <seal/evaluator.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace seal;

void bind_evaluator(py::module &m) {
    py::class_<Evaluator>(m, "Evaluator")
        .def(py::init<const SEALContext &>(), py::arg("context"))

        // Addition
        .def("add", [](Evaluator &e, const Ciphertext &a, const Ciphertext &b, Ciphertext &out) { e.add(a, b, out); })
        .def("add_inplace", [](Evaluator &e, Ciphertext &a, const Ciphertext &b) { e.add_inplace(a, b); })
        .def("add_many", [](Evaluator &e, const std::vector<Ciphertext> &operands, Ciphertext &destination) { e.add_many(operands, destination); })
        .def("add_plain", [](Evaluator &e, Ciphertext &a, const Plaintext &b) { e.add_plain_inplace(a, b); })
        .def("add_plain_out", [](Evaluator &e, const Ciphertext &a, const Plaintext &b, Ciphertext &out) { e.add_plain(a, b, out); })

        // Subtraction
        .def("sub", [](Evaluator &e, const Ciphertext &a, const Ciphertext &b, Ciphertext &out) { e.sub(a, b, out); })
        .def("sub_inplace", [](Evaluator &e, Ciphertext &a, const Ciphertext &b) { e.sub_inplace(a, b); })
        .def("sub_plain", [](Evaluator &e, Ciphertext &a, const Plaintext &b) { e.sub_plain_inplace(a, b); })
        .def("sub_plain_out", [](Evaluator &e, const Ciphertext &a, const Plaintext &b, Ciphertext &out) { e.sub_plain(a, b, out); })

        // Negation
        .def("negate", [](Evaluator &e, const Ciphertext &a, Ciphertext &out) { e.negate(a, out); })
        .def("negate_inplace", [](Evaluator &e, Ciphertext &a) { e.negate_inplace(a); })

        // Multiplication
        .def("multiply", [](Evaluator &e, const Ciphertext &a, const Ciphertext &b, Ciphertext &out) { e.multiply(a, b, out); })
        .def("multiply_inplace", [](Evaluator &e, Ciphertext &a, const Ciphertext &b) { e.multiply_inplace(a, b); })
        .def("multiply_many", [](Evaluator &e, const std::vector<Ciphertext> &operands, const RelinKeys &relin_keys, Ciphertext &destination) { e.multiply_many(operands, relin_keys, destination); })
        .def("multiply_plain", [](Evaluator &e, Ciphertext &a, const Plaintext &b) { e.multiply_plain_inplace(a, b); })
        .def("multiply_plain_out", [](Evaluator &e, const Ciphertext &a, const Plaintext &b, Ciphertext &out) { e.multiply_plain(a, b, out); })
        .def("square", [](Evaluator &e, const Ciphertext &a, Ciphertext &out) { e.square(a, out); })
        .def("square_inplace", [](Evaluator &e, Ciphertext &a) { e.square_inplace(a); })

        // Relinearization
        .def("relinearize", [](Evaluator &e, const Ciphertext &a, const RelinKeys &relin_keys, Ciphertext &out) { e.relinearize(a, relin_keys, out); })
        .def("relinearize_inplace", [](Evaluator &e, Ciphertext &a, const RelinKeys &relin_keys) { e.relinearize_inplace(a, relin_keys); })

        // Exponentiation
        .def("exponentiate", [](Evaluator &e, const Ciphertext &a, std::uint64_t exponent, const RelinKeys &relin_keys, Ciphertext &out) { e.exponentiate(a, exponent, relin_keys, out); })
        .def("exponentiate_inplace", [](Evaluator &e, Ciphertext &a, std::uint64_t exponent, const RelinKeys &relin_keys) { e.exponentiate_inplace(a, exponent, relin_keys); })

        // Modulus switching
        .def("mod_switch_to_next", [](Evaluator &e, const Ciphertext &a, Ciphertext &out) { e.mod_switch_to_next(a, out); })
        .def("mod_switch_to_next_inplace", [](Evaluator &e, Ciphertext &a) { e.mod_switch_to_next_inplace(a); })
        .def("mod_switch_to", [](Evaluator &e, const Ciphertext &a, parms_id_type parms_id, Ciphertext &out) { e.mod_switch_to(a, parms_id, out); })
        .def("mod_switch_to_inplace", [](Evaluator &e, Ciphertext &a, parms_id_type parms_id) { e.mod_switch_to_inplace(a, parms_id); })
        .def("mod_switch_to_next_plain_inplace", [](Evaluator &e, Plaintext &a) { e.mod_switch_to_next_inplace(a); })
        .def("mod_switch_to_plain_inplace", [](Evaluator &e, Plaintext &a, parms_id_type parms_id) { e.mod_switch_to_inplace(a, parms_id); })

        // Rescale (CKKS)
        .def("rescale_to_next", [](Evaluator &e, Ciphertext &a) { e.rescale_to_next_inplace(a); })
        .def("rescale_to", [](Evaluator &e, Ciphertext &a, parms_id_type parms_id) { e.rescale_to_inplace(a, parms_id); })

        // Rotation and Galois
        .def("rotate_rows", [](Evaluator &e, const Ciphertext &a, int steps, const GaloisKeys &galois_keys, Ciphertext &out) { e.rotate_rows(a, steps, galois_keys, out); })
        .def("rotate_rows_inplace", [](Evaluator &e, Ciphertext &a, int steps, const GaloisKeys &galois_keys) { e.rotate_rows_inplace(a, steps, galois_keys); })
        .def("rotate_columns", [](Evaluator &e, const Ciphertext &a, const GaloisKeys &galois_keys, Ciphertext &out) { e.rotate_columns(a, galois_keys, out); })
        .def("rotate_columns_inplace", [](Evaluator &e, Ciphertext &a, const GaloisKeys &galois_keys) { e.rotate_columns_inplace(a, galois_keys); })
        .def("rotate_vector", [](Evaluator &e, const Ciphertext &a, int steps, const GaloisKeys &galois_keys, Ciphertext &out) { e.rotate_vector(a, steps, galois_keys, out); })
        .def("rotate_vector_inplace", [](Evaluator &e, Ciphertext &a, int steps, const GaloisKeys &galois_keys) { e.rotate_vector_inplace(a, steps, galois_keys); })
        .def("apply_galois", [](Evaluator &e, const Ciphertext &a, std::uint32_t galois_elt, const GaloisKeys &galois_keys, Ciphertext &out) { e.apply_galois(a, galois_elt, galois_keys, out); })
        .def("apply_galois_inplace", [](Evaluator &e, Ciphertext &a, std::uint32_t galois_elt, const GaloisKeys &galois_keys) { e.apply_galois_inplace(a, galois_elt, galois_keys); })

        // Complex conjugation (CKKS)
        .def("complex_conjugate", [](Evaluator &e, const Ciphertext &a, const GaloisKeys &galois_keys, Ciphertext &out) { e.complex_conjugate(a, galois_keys, out); })
        .def("complex_conjugate_inplace", [](Evaluator &e, Ciphertext &a, const GaloisKeys &galois_keys) { e.complex_conjugate_inplace(a, galois_keys); })

        // Plaintext operations
        .def("multiply_plain_inplace", [](Evaluator &e, Ciphertext &a, const Plaintext &b) { e.multiply_plain_inplace(a, b); })
        .def("add_plain_inplace", [](Evaluator &e, Ciphertext &a, const Plaintext &b) { e.add_plain_inplace(a, b); })
        .def("sub_plain_inplace", [](Evaluator &e, Ciphertext &a, const Plaintext &b) { e.sub_plain_inplace(a, b); })

        // NTT transforms
        .def("transform_to_ntt_inplace", [](Evaluator &e, Ciphertext &a) { e.transform_to_ntt_inplace(a); })
        .def("transform_from_ntt_inplace", [](Evaluator &e, Ciphertext &a) { e.transform_from_ntt_inplace(a); })
        .def("transform_to_ntt", [](Evaluator &e, const Ciphertext &a, Ciphertext &out) { e.transform_to_ntt(a, out); })
        .def("transform_from_ntt", [](Evaluator &e, const Ciphertext &a, Ciphertext &out) { e.transform_from_ntt(a, out); })
        .def("transform_to_ntt_plain_inplace", [](Evaluator &e, Plaintext &a, parms_id_type parms_id) { e.transform_to_ntt_inplace(a, parms_id); })
        ;
}