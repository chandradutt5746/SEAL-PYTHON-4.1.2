#include <pybind11/pybind11.h>
#include <seal/seal.h>
#include <pybind11/stl.h>
// #include "bind_advanced.h"
#include "bind_batchencoder.h"
#include "bind_ckksencoder.h"
#include "bind_decryptor.h"
#include "bind_encryptor.h"
#include "bind_evaluator.h"
#include "bind_plaintext.h"
#include "bind_random.h"
#include "bind_encryption.h"
#include "bind_context.h"
#include "bind_keys.h"
#include "bind_ciphertext.h"
#include "bind_util.h"
#include "bind_coeffmodulus.h"
#include "bind_plainmodulus.h"
#include "bind_serialization.h"
#include "bind_modulus.h"
#include "bind_security.h" 


namespace py = pybind11;
using namespace seal;

PYBIND11_MODULE(seal, m) {
    m.doc() = "Microsoft SEAL 4.1.2 Python Bindings";
    
    m.attr("__version__") = "4.1.2";

    // Bind enums
    py::enum_<scheme_type>(m, "SchemeType")
        .value("BFV", scheme_type::bfv)
        .value("CKKS", scheme_type::ckks)
        .value("BGV", scheme_type::bgv);
        
    py::enum_<sec_level_type>(m, "SecLevelType")
        .value("TC128", sec_level_type::tc128)
        .value("TC192", sec_level_type::tc192)
        .value("TC256", sec_level_type::tc256);

    
    bind_coeffmodulus(m);
    bind_plainmodulus(m);
    bind_encryption_parameters(m);
    bind_context(m);
    bind_keys(m);
    bind_ciphertext(m);
    // bind_encoder(m);
    bind_evaluator(m);
    bind_serialization(m);
    bind_security_utils(m);
    bind_modulus(m);
    bind_plaintext(m);
    bind_batchencoder(m);
    bind_ckksencoder(m);
    bind_decryptor(m);
    bind_encryptor(m);
    bind_random(m);
    // bind_advanced(m); 
    // bind_util(m);
    bind_security(m);
    // bind_encryption(m);
    
    
    m.def("secure_erase", [](std::string &s) {
        seal::util::seal_memzero(s.data(), s.size());
        s.clear();
    });
}