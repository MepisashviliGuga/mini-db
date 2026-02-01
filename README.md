# MiniDB: A Custom C++ Database Engine

MiniDB is a persistent key-value store built from scratch to explore low-level systems engineering concepts.  
Built by **Guga** and **Dato**.

## 🎯 Project Goals
- Understand how databases work at a low level
- Practice memory management and data structures in C++
- Build a simple SQL-like interface from scratch
- Gain experience with real-world Git workflows and collaboration

## 🚀 Current Features
- **Phase 1 (Complete):**
  - In-memory storage engine
  - Interactive SQL-like REPL
- **Supported commands:**
  - `insert`
  - `select`
  - `exit`

## 🛠 Project Structure
- `src/` — Source code (`main.cpp`)
- `include/` — Header files (`db.h`)
- `python_client/` — Planned future client SDK

## 💻 How to Build & Run

### Prerequisites
- CMake
- C++ compiler (GCC or MinGW)

### Build Steps
```bash
mkdir build
cd build
cmake ..
cmake --build .
