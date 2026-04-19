# sysguard
A lightweight system health monitoring and early-warning tool for Linux-based systems

## Build
```bash
cmake -S . -B build
cmake --build build
```

## Test
```bash
ctest --test-dir build
```

## Run
```bash
./build/sysguard
```
