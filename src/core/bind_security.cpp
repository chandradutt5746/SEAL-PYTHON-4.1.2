// bind_security.cpp
#include <seal/util/common.h>
#include <seal/memorymanager.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace seal;
using namespace seal::util;

void bind_security(py::module &m) {
    m.def("secure_erase", [](std::string &s) {
        seal_memzero(s.data(), s.size());
        s.clear();
    });
    
    m.def("set_global_memory_pool", [](MemoryPoolHandle handle) {
        MemoryManager::GetPool() = handle;
    });
    
    py::class_<MemoryPoolHandle>(m, "MemoryPoolHandle")
        .def(py::init<>())
        .def_static("New", []() { return MemoryPoolHandle::New(); })
        .def_static("Global", []() { return MemoryPoolHandle::Global(); });
}