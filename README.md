# Hexagonal Pattern

A C++ project demonstrating the **Hexagonal Architecture (Ports & Adapters)** pattern, with a graphical interface to generate and visualize hexagonal patterns.

---

## Features
- Implements **Hexagonal Architecture**:
  - **Domain Layer:** Core business logic
  - **Ports:** Interfaces for input/output
  - **Adapters:** GUI and other implementations
- GUI rendering of hexagonal patterns using **ImGui**
- Modular and reusable code
- Easily extendable for different pattern configurations

---

## Project Structure

**Hexagonal Architecture Layers:**
- **Domain Layer:** Core logic for generating hexagonal patterns
- **Ports:** Interfaces that define communication between layers
- **Adapters:** GUI adapter using ImGui to display the patterns

---

## Build & Run

### Using Visual Studio
1. Clone the repository:
   ```bash
   git clone https://github.com/rfcm-git/HexagonalPattern.git
