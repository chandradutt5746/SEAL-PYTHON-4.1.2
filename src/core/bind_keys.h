#ifndef SEAL_PYTHON_BIND_KEYS_H
#define SEAL_PYTHON_BIND_KEYS_H

#include <seal/publickey.h>
#include <seal/secretkey.h>
#include <seal/relinkeys.h>
#include <seal/galoiskeys.h>
#include <seal/keygenerator.h>  // Add missing include
#include <pybind11/pybind11.h>

void bind_keys(pybind11::module &m);

#endif // SEAL_PYTHON_BIND_KEYS_H