#!/bin/bash
set -e

# Activate virtual environment
source .venv/bin/activate

# Find pybind11 installation
PYBIND11_PATH=$(python -c "import pybind11; print(pybind11.get_include())" | sed 's/include$//')

# Create build directory
rm -rf build
mkdir -p build
cd build

# Configure with CMake
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -Dpybind11_DIR="$PYBIND11_PATH/share/cmake/pybind11" \
    -DSEAL_USE_INTEL_HEXL=ON \
    -DSEAL_BUILD_TESTS=ON \
    -DSEAL_BUILD_EXAMPLES=ON \
    -DSEAL_BUILD_SEAL_C=ON \
    -GNinja

# Build with Ninja
cmake --build . -- -j$(nproc)

# NEW: Copy from the correct output location
cp python/seal.so ../python/
mkdir -p ../seal
cp python/seal.so ../seal/
cp ../python/__init__.py ../seal/

echo "Build successful! Module saved to python/"
echo "Test with: cd python && python -c 'import seal'"