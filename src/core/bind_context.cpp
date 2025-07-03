#include "bind_context.h"
#include <seal/context.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace seal;

void bind_context(py::module &m) {
    // Bind EncryptionParameterQualifiers
    py::class_<EncryptionParameterQualifiers>(m, "EncryptionParameterQualifiers")
        .def_property_readonly("parameters_set", [](const EncryptionParameterQualifiers &q) { return q.parameters_set(); })
        .def_property_readonly("using_fft", [](const EncryptionParameterQualifiers &q) { return q.using_fft; })
        .def_property_readonly("using_ntt", [](const EncryptionParameterQualifiers &q) { return q.using_ntt; })
        .def_property_readonly("using_batching", [](const EncryptionParameterQualifiers &q) { return q.using_batching; })
        .def_property_readonly("using_fast_plain_lift", [](const EncryptionParameterQualifiers &q) { return q.using_fast_plain_lift; })
        .def_property_readonly("using_descending_modulus_chain", [](const EncryptionParameterQualifiers &q) { return q.using_descending_modulus_chain; })
        .def_property_readonly("sec_level", [](const EncryptionParameterQualifiers &q) { return q.sec_level; })
        .def_property_readonly("parameter_error", [](const EncryptionParameterQualifiers &q) { return q.parameter_error; })
        .def_property_readonly("parameter_error_name", [](const EncryptionParameterQualifiers &q) { return q.parameter_error_name(); })
        .def_property_readonly("parameter_error_message", [](const EncryptionParameterQualifiers &q) { return q.parameter_error_message(); });

    // Bind ContextData
    py::class_<SEALContext::ContextData, std::shared_ptr<SEALContext::ContextData>>(m, "ContextData")
        .def_property_readonly("parms", [](const SEALContext::ContextData &cd) {
        // Return a copy of EncryptionParameters
        return cd.parms();
    })
    .def_property_readonly("parms_id", [](const SEALContext::ContextData &cd) {
        auto id = cd.parms_id();
        return py::bytes(reinterpret_cast<const char*>(id.data()), id.size());
    })
    .def_property_readonly("qualifiers", [](const SEALContext::ContextData &cd) {
        // Return a copy of EncryptionParameterQualifiers
        return cd.qualifiers();
    })
    .def_property_readonly("chain_index", &SEALContext::ContextData::chain_index)
    .def_property_readonly("next_context_data", [](const SEALContext::ContextData &cd) {
        // Return a shared_ptr to the next context data (or None)
        auto next = cd.next_context_data();
        return next ? next : std::shared_ptr<SEALContext::ContextData>();
    })
    .def_property_readonly("prev_context_data", [](const SEALContext::ContextData &cd) {
        // Return a shared_ptr to the previous context data (or None)
        auto prev = cd.prev_context_data();
        return prev ? prev : std::shared_ptr<SEALContext::ContextData>();
    });

    // Bind SEALContext
    py::class_<SEALContext, std::shared_ptr<SEALContext>>(m, "SEALContext")
        .def(py::init([](const EncryptionParameters &parms, 
                        bool expand_mod_chain = true, 
                        sec_level_type sec_level = sec_level_type::tc128) {
            return std::make_shared<SEALContext>(parms, expand_mod_chain, sec_level);
        }), py::arg("parms"), 
            py::arg("expand_mod_chain") = true, 
            py::arg("sec_level") = sec_level_type::tc128)
        .def("parameters_set", &SEALContext::parameters_set)
        .def("key_parms_id", [](const SEALContext &ctx) {
            auto id = ctx.key_parms_id();
            return py::bytes(reinterpret_cast<const char*>(id.data()), id.size());
        })
        .def("first_parms_id", [](const SEALContext &ctx) {
            auto id = ctx.first_parms_id();
            return py::bytes(reinterpret_cast<const char*>(id.data()), id.size());
        })
        .def("last_parms_id", [](const SEALContext &ctx) {
            auto id = ctx.last_parms_id();
            return py::bytes(reinterpret_cast<const char*>(id.data()), id.size());
        })
        .def("key_context_data", &SEALContext::key_context_data)
        .def("first_context_data", &SEALContext::first_context_data)
        .def("last_context_data", &SEALContext::last_context_data)
        .def("get_context_data", &SEALContext::get_context_data)
        .def("using_keyswitching", &SEALContext::using_keyswitching);
}