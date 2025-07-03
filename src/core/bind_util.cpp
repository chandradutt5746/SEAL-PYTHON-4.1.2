#include <seal/seal.h>
#include <seal/memorymanager.h>
#include <seal/util/common.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace seal;
using namespace seal::util;

void bind_security_utils(py::module &m) {
    m.def("secure_erase", [](std::string &s) {
        util::seal_memzero(s.data(), s.size());
        s.clear();
    });
    
    m.def("disable_memory_pool", []() {
        MemoryManager::GetPool() = MemoryPoolHandle::New();
    });
}