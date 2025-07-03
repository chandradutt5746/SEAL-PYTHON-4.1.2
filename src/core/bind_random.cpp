#include <seal/randomgen.h>
#include <pybind11/pybind11.h>
#include "bind_random.h"
#include <random>
#include <fstream>

namespace py = pybind11;
using namespace seal;

void bind_random(py::module &m) {
    // Expose prng_type enum
    py::enum_<prng_type>(m, "prng_type")
        .value("unknown", prng_type::unknown)
        .value("blake2xb", prng_type::blake2xb)
        .value("shake256", prng_type::shake256);

    // Expose UniformRandomGeneratorInfo
    py::class_<UniformRandomGeneratorInfo>(m, "UniformRandomGeneratorInfo")
        .def(py::init<>())
        .def("type", [](const UniformRandomGeneratorInfo &self) { return self.type(); })
        .def("seed", py::overload_cast<>(&UniformRandomGeneratorInfo::seed, py::const_))
        .def("has_valid_prng_type", &UniformRandomGeneratorInfo::has_valid_prng_type)
        .def("save", [](const UniformRandomGeneratorInfo &self, const std::string &path) {
            std::ofstream out(path, std::ios::binary);
            if (!out) throw std::runtime_error("Failed to open file: " + path);
            self.save(out, compr_mode_type::none);
            if (!out.good()) throw std::runtime_error("Failed to write to file: " + path);
        })
        .def("load", [](UniformRandomGeneratorInfo &self, const std::string &path) {
            std::ifstream in(path, std::ios::binary);
            if (!in) throw std::runtime_error("Failed to open file: " + path);
            self.load(in);
            in.close();
        });

    // Expose UniformRandomGeneratorFactory and DefaultFactory
    py::class_<UniformRandomGeneratorFactory, std::shared_ptr<UniformRandomGeneratorFactory>>(m, "UniformRandomGeneratorFactory")
        .def_static("DefaultFactory", &UniformRandomGeneratorFactory::DefaultFactory, py::return_value_policy::reference)
        .def("use_random_seed", &UniformRandomGeneratorFactory::use_random_seed)
        .def("default_seed", &UniformRandomGeneratorFactory::default_seed)
        .def("create", [](UniformRandomGeneratorFactory &self) {
            return self.create();
        })
        .def("create_with_seed", [](UniformRandomGeneratorFactory &self, prng_seed_type seed) {
            return self.create(seed);
        });

    // Expose UniformRandomGenerator (minimal, for demonstration)
    py::class_<UniformRandomGenerator, std::shared_ptr<UniformRandomGenerator>>(m, "UniformRandomGenerator")
        .def("generate", [](UniformRandomGenerator &self, std::size_t n) {
            std::vector<uint8_t> buf(n);
            self.generate(n, reinterpret_cast<seal::seal_byte*>(buf.data()));
            return py::bytes(reinterpret_cast<const char*>(buf.data()), n);
        })
        .def("seed", &UniformRandomGenerator::seed)
        .def("info", &UniformRandomGenerator::info);

    // Expose Blake2xbPRNGFactory and Shake256PRNGFactory
    py::class_<Blake2xbPRNGFactory, UniformRandomGeneratorFactory, std::shared_ptr<Blake2xbPRNGFactory>>(m, "Blake2xbPRNGFactory")
        .def(py::init<>())
        .def(py::init<prng_seed_type>());

    py::class_<Shake256PRNGFactory, UniformRandomGeneratorFactory, std::shared_ptr<Shake256PRNGFactory>>(m, "Shake256PRNGFactory")
        .def(py::init<>())
        .def(py::init<prng_seed_type>());

    // Expose prng_seed_type as a Python list of 8 uint64_t
    py::class_<prng_seed_type>(m, "prng_seed_type")
        .def(py::init<>())
        .def("__getitem__", [](const prng_seed_type &seed, size_t i) { return seed[i]; })
        .def("__setitem__", [](prng_seed_type &seed, size_t i, uint64_t v) { seed[i] = v; })
        .def("__len__", [](const prng_seed_type &) { return prng_seed_uint64_count; });

    // Utility: get a random seed from the OS
    m.def("random_seed", []() {
        prng_seed_type seed;
        seal::random_bytes(reinterpret_cast<seal_byte *>(seed.data()), prng_seed_byte_count);
        return seed;
    }, "Returns a random prng_seed_type from the OS.");
}