set -e
cmake -B build -DNSPL_BUILD_EXAMPLES=ON -G Ninja .
cmake --build build
./build/NSPLApp