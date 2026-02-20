# MiniDB: A Custom C++ Database Engine

A persistent, paged storage engine built from scratch to explore low-level systems engineering and database internals.

## 🚀 Project Status: Phase 3 (Architecture & Paging) Complete

### 🏗️ Current Architecture
The engine has transitioned from a simple in-memory vector to a **Paged Storage Architecture**. 

- **Pager:** Manages 4KB blocks (Pages) of binary data. It includes a **Buffer Pool (Cache)** to minimize Disk I/O by keeping recently used pages in RAM.
- **Table:** Handles logical-to-physical mapping. It calculates exactly which Page and which Offset a specific Row ID belongs to.
- **Persistence:** Implementation of a custom serialization layer using `reinterpret_cast` and binary `fstream` to ensure data survives process restarts.

### 🛠️ Key Technical Concepts Implemented
- **Memory Alignment:** Ensuring rows do not cross 4KB page boundaries to optimize hardware read cycles.
- **Buffer Management:** A cache system that prevents multiple allocations of the same page and manages the lifecycle of heap-allocated memory.
- **RAII (Resource Acquisition Is Initialization):** Using C++ destructors to ensure file handles are closed and buffered data is flushed to disk safely on exit.
- **Pointer Arithmetic:** Manual calculation of memory offsets for data retrieval.

## 💻 How to Build & Run
**Prerequisites:** CMake and a C++17 compatible compiler (GCC/Clang/MSVC).

```bash
mkdir build
cd build
cmake ..
cmake --build .
./minidb