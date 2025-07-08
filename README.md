# SEAL-PYTHON-4.1.2

**Author:** Chandradutt Patel
**LinkedIn:** https://github.com/chandradutt5746

A Python binding for [Microsoft SEAL](https://github.com/microsoft/SEAL), enabling easy-to-use homomorphic encryption in Python. This project allows you to perform encrypted computation on real numbers using the CKKS scheme, with support for serialization, bootstrapping, and more.

**Developed and maintained by Chandradutt Patel**
---

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation](#installation)
  - [From GitHub](#from-github)
  - [Build Instructions](#build-instructions)
- [Quick Start](#quick-start)
- [Usage Examples](#usage-examples)
- [Testing](#testing)
- [Troubleshooting](#troubleshooting)
- [Security Notes](#security-notes)
- [References](#references)
- [License](#license)
- [Acknowledgments](#acknowledgments)
- [Contact](#contact)

---

## Features

- Python bindings for Microsoft SEAL 4.1.2
- CKKS, BFV, and BGV schemes for encrypted computation
- Serialization and deserialization of ciphertexts and keys
- Example scripts for batching
- Beginner-friendly code and debug output for learning.

---

## Project Structure

```
.
├── build.sh                # Build script
├── clean.sh                # Clean build artifacts
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This file
├── setup.py                # Python package setup
├── python/                 # Python bindings and test scripts
│   ├── seal.so             # Compiled Python extension
│   ├── test_ckks.py
│   └── test_bfv_and_bgv.py
├── seal/                   # Python package directory
│   ├── __init__.py
│   └── seal.so
├── src/                    # C++ binding sources
│   └── core/
├── third_party/SEAL/       # Official Microsoft SEAL source
└── ...
```

---

## Requirements

**Install requirements.txt file for the important packages**
```sh
    pip install -r requirements.txt
```
- Python 3.8+
- C++17 compatible compiler (GCC >= 7, Clang >= 5)
- [CMake](https://cmake.org/) >= 3.13
- [pybind11](https://github.com/pybind/pybind11) (installed automatically if using the provided scripts)
- (Linux) `build-essential`, `python3-dev`, `ninja-build` recommended

---

## Installation

### From GitHub

Clone the repository:

```sh
git clone https://github.com/yourusername/SEAL-PYTHON-4.1.2.git
cd SEAL-PYTHON-4.1.2
```
## Getting Microsoft SEAL Do not SKIP THIS STEP

This binding requires the official [Microsoft SEAL](https://github.com/microsoft/SEAL) library.

**Before building, clone SEAL into the `third_party/` directory:**

```sh
git clone https://github.com/microsoft/SEAL.git third_party/SEAL
```

### Build Instructions

1. **Create a Python virtual environment (recommended):**

```sh
    python3 -m venv .venv
    source .venv/bin/activate
```

2. **Install Python dependencies:**

```sh
    pip install -r requirements.txt
```

3. **Build the C++ extension and SEAL library:**

```sh
    ./build.sh
```

    This will compile Microsoft SEAL and the Python bindings. The resulting `seal.so` will be placed in the `python/` directory.

    **If you do not have `build.sh`, you can build manually:**

    ```sh
    mkdir -p build
    cd build
    cmake ..
    make -j$(nproc)
    cd ..
    ```

4. **(Optional) Install as a Python package:**
    
    ### If you want to use SEAL Library globally in your system run this command to install SEAL Globally.
    
```sh
            pip install .
```

    This will install the package globally or in your virtual environment.
---

## Quick Start

After building, you can run the example scripts:
### In this 'python' folder you will find seal.so file after building the Python Binding.
### Do not Remove this file otherwise you have to build the seal again.

#### for basic understanding just try to open the test_bfv_and_bgv.py file and learn. after That you can move to bootstrapping.py file for advanced operations.
```sh
cd python
python test_bfv_and_bgv.py
python test_bootstrapping.py
```

- The `seal.so` file must be present in the `python/` directory for imports to work.
- **Do not remove `seal.so`** unless you plan to rebuild.

---

## Usage Examples
## Testing

You can run the provided test scripts:

```sh
cd python
python test_bootstrapping.py
python test_bfv_and_bgv.py
```

---

## Troubleshooting

- **Build errors:** Ensure you have a C++17 compiler and all dependencies installed.
- **Import errors:** Make sure `seal.so` is in your `PYTHONPATH` or in the same directory as your script.
- **Empty decode results:** Ensure you are using the latest binding code and returning vectors from C++ to Python.
- **Debugging:** The example scripts include `[DEBUG]` print statements to help trace computation steps.
- **Virtual environment:** If you have issues, try running everything inside a fresh Python virtual environment.
---

## Security Notes

- **No secrets or credentials** are included in this repository.
- **Do not share your secret keys** or decrypted data.
- **Review all dependencies** and keep them up to date.
- **For research and educational use only.** Not for production or handling sensitive data without a full security review.

---

## References

- [Microsoft SEAL Documentation](https://github.com/microsoft/SEAL)
- [Homomorphic Encryption Standardization](https://homomorphicencryption.org/)
- [pybind11 Documentation](https://pybind11.readthedocs.io/en/stable/)

---

## License

Copyright (c) 2025 Chandradutt Patel

This project is licensed under the MIT License. See [third_party/SEAL/LICENSE](third_party/SEAL/LICENSE) for Microsoft SEAL's license.

---

## Acknowledgments

- Microsoft SEAL team for the core library
- pybind11 for Python bindings
- Chandradutt Patel for the Python binding and packaging

---

## Contact

For collaboration, questions, or contributions, please:
- Open an issue or pull request on GitHub
- Connect on [LinkedIn](https://www.linkedin.com/in/cnpatel5746/)

---

*Happy encrypting!*