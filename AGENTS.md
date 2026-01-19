# Agent Notes

## Project Expectations
- This workspace uses CCS/Eclipse project files (`.project`, `.cproject`). Do not introduce a new build system unless asked.
- Keep C and C++ sources separated by their existing layout to avoid compiler mode issues.
- Keep linker command files (`*.cmd`) at the project root; CCS configs reference them there.
- Do not change file extensions from `.c` to `.cc` (or vice versa) unless the code is verified for that language.
- `.settings` files can be user- or workspace-specific. Ask before committing changes to them.
- Follow the `.gitignore` for build outputs and generated files.

## C28x C++03 Coding Policy (C-with-classes)
Scope: all code built with the C28x toolchain (CPU1/CPU2) on F28388D.
Goal: keep real-time determinism and debuggability equivalent to C, while allowing minimal C++03 structure for initialization and peripheral access.

### Core Principle
Use C++03 as a strict C subset. Classes are permitted only as zero-overhead organization tools (namespacing, typed wrappers, explicit init).
No hidden runtime behavior. All side effects must be explicit and invoked from controlled init code paths.

### Hard Bans (MUST NOT)
1) Exceptions and RTTI
- `throw`, `try/catch`, exception specifications
- `dynamic_cast`, `typeid`

2) Dynamic memory
- `new`, `delete`, `new[]`, `delete[]`
- Any allocator-based containers or ownership patterns requiring heap

3) Virtual dispatch / inheritance polymorphism
- `virtual` functions, vtables, runtime polymorphism
- Inheritance used as an architectural pattern (composition only)

4) Heavy / non-deterministic standard library usage
- iostreams (`<iostream>`, `<sstream>`, locales)
- Anything that can pull in large runtime support or non-obvious global initialization

5) Global/Static objects with non-trivial initialization
- No constructors that run before `main()`
- No file-scope objects whose initialization has side effects (register writes, IPC, peripheral setup)

### Allowed C++03 Features (MAY)
- `namespace` (recommended), `enum`, `struct`, `class` (restricted as below)
- `static inline` functions in headers for zero-overhead wrappers
- Templates only when they are simple, bounded, and do not cause code-size explosion
- Overloading for clarity (avoid ambiguous implicit conversions)

### Class Usage Rules (MUST)
1) No RAII side effects
- Constructors/destructors must not touch hardware registers, IPC, clocks, or peripherals.
- All hardware side effects must live in explicit `init()` / `deinit()` / `enable()` / `disable()` methods.

2) Prefer "no-instance" wrappers
- Use `struct` with `static inline` methods to emulate namespacing and provide typed access.

3) If instances are necessary
- Instances must be POD-like (plain pointers/handles), created and initialized explicitly in `main()` (or a designated init phase).
- No dynamic lifetime management; no hidden ownership transfers.

### Initialization Policy (MUST)
All initialization must be explicit and centrally orchestrated.
- All hardware/peripheral init must be called from a single, well-defined init sequence:
  `SystemInit()` -> `BoardInit()` -> `AppInit()`
- No implicit init via global constructors.
- If an init order dependency exists, it must be documented at the call site.

### Real-Time Safety Rules (MUST)
- ISR paths must be bounded and predictable.
- No blocking waits/spins in ISR (except minimal, documented, bounded sequences).
- No logging/printf in ISR.
- Shared data between ISR and background tasks must use explicit synchronization primitives (volatile, critical sections, ring buffers, etc.) approved for the project.

### Peripheral Wrapper Pattern (Recommended)
Preferred pattern: "no-instance" wrapper with explicit init.

```cpp
struct Epwm1
{
    static inline void init()
    {
        // EALLOW; configure regs; EDIS;
    }

    static inline void set_cmpa(uint16_t v)
    {
        // EPwm1Regs.CMPA.bit.CMPA = v;
    }
};
```
