*This project has been created as part of the 42 curriculum by hamossai.*

---

# ft_printf

## Description

`ft_printf` is a custom re-implementation of the standard C library function `printf()`. The primary goal of this project is to discover and master the concept of **variadic functions** (`stdarg.h`) in C. By building a robust formatting engine from scratch, this project strengthens low-level programming skills, modular function design, and precise character tracking (`va_list` management).

The project is split into two parts, each in its own folder (`mandatory/` and `bonus/`), with its own header and sources.

### Mandatory part

Handles the core format specifiers (`%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, and `%%`) without relying on external libraries, using a custom set of lightweight helper files:

* `ft_printf.c` (Core parsing and routing)
* `ft_print_char.c` (Character & percent handling)
* `ft_putstr.c` (String handling & `NULL` checks)
* `ft_putnbr.c` (Signed integer & `INT_MIN` handling)
* `ft_uputnbr.c` (Unsigned decimal formatting)
* `ft_print_hex.c` (Hexadecimal conversion for `%x`, `%X`)
* `ft_print_address.c` (Pointer memory formatting & `(nil)` handling)
* `ft_helper.c` (Helper functions)
* `ft_printf.h` (Header declarations and prototypes)

### Bonus part

Extends the mandatory part with the following **flags** and **field width**, combinable in any order:

| Flag / option | Meaning |
|---------------|---------|
| `-` | Left-justify the output inside the field width |
| `0` | Pad with zeros instead of spaces (ignored if `-` or a precision is given for integers) |
| `.` | Precision (minimum digits for numbers, maximum characters for `%s`) |
| `#` | Alternate form: prefix `0x` / `0X` for non-zero `%x` / `%X` |
| `+` | Always print the sign of a signed number |
| ` ` (space) | Print a space before a non-negative signed number |
| width | Minimum field width (a number written before the conversion) |

Which options each conversion uses or ignores:

| Conversion | Uses | Ignores |
|------------|------|---------|
| `d` `i` | `-` `+` space `0` width `.prec` | `#` |
| `u` | `-` `0` width `.prec` | `#` `+` space |
| `x` `X` | `#` `-` `0` width `.prec` | `+` space |
| `c` | `-` width | `#` `+` space `0` `.prec` |
| `s` | `-` width `.prec` | `#` `+` space `0` |
| `p` | `-` width | `#` `+` space `0` `.prec` |

Bonus source files:

* `ft_printf_bonus.c` (Format string parsing, flag/width/precision reading, routing)
* `helper_functions_bonus.c` (Helper functions)
* `ft_putnbr_bonus.c` (Signed integer `%d` `%i` with sign, padding and precision)
* `ft_uputnbr_bonus.c` (Unsigned decimal `%u`)
* `ft_hex_parser_bonus.c` (Hexadecimal `%x` `%X` with `#` flag)
* `ft_address_parser_bonus.c` (Pointer `%p` with width, `-` and `(nil)` handling)
* `ft_char_parser_bonus.c` (Character `%c` with width and `-`)
* `ft_string_parser_bonus.c` (String `%s` with width, `-`, precision and `(null)`)
* `numbers_utiles_bonus.c` (Shared helpers: length computation, sign, padding)
* `ft_printf_bonus.h` (Header, `t_form` structure and prototypes)

---

## Algorithm & Technical Choices

### Flowchart Architecture (for mandatory part)

The core logic relies on a sequential pass through the format string using a modular routing approach. The flowchart below shows how the format string is read character by character, how each `%` conversion is routed to its dedicated helper, and how the printed-character count is accumulated and returned.

![ft_printf Flowchart](https://raw.githubusercontent.com/Yuuuri01/PRINTF_42/main/Blank%20diagram.svg)

### Algorithm Justification

The format string is traversed **once, from left to right (O(n))**. Regular characters are written directly. When a `%` is found, the next character is read and dispatched to the matching helper function. This keeps `ft_printf` itself small, makes each conversion independently testable, and respects the 42 Norm (short functions, limited scope).

In the bonus, after the `%` the parser reads, in order: the **flags** (`-`, `0`, `#`, `+`, space), the **width**, the optional **precision** (`.` followed by digits), and finally the **conversion specifier**. Everything is gathered first and only then printed, because the amount of padding depends on the total length of the output (digits, sign, prefix). Each conversion therefore follows the same three steps:

1. Compute the length of the value (digits, sign, `0x` prefix).
2. Compute the padding (spaces and zeros) from width, precision and flags.
3. Print in the right order: left spaces, sign/prefix, zeros, value, right spaces.

### Data Structure Justification

No complex data structure is needed, and this is intentional:

* **`va_list`** is the only structure used to walk through the variable arguments, as it is the standard and portable mechanism for variadic functions.
* **An `int` counter** accumulates the number of printed characters. Each helper returns its own count, so the final sum matches the return value of the real `printf`.
* **Recursion** is used for number conversion (`%d`, `%u`, `%x`, `%X`, `%p`). It avoids allocating a temporary buffer, so there is no `malloc` and no risk of memory leaks.
* **`t_form` structure (bonus only)** stores the parsed options of one conversion (`minus`, `zero`, `hash`, `plus`, `space`, `width`, `precision`, `len`, `spec`, and the computed `zero_padding` / `sp_padding`). A single structure passed by pointer avoids long parameter lists (the Norm limits a function to 4 parameters) and keeps every parser function uniform. It is reset before each conversion so that flags never leak from one `%` to the next.

### Technical Implementation Details

1. **Variadic Argument Management:** Uses `va_start`, `va_arg`, and `va_end` macros to dynamically parse arguments passed past the format string.
2. **Character Counting:** Every helper function returns the exact number of characters successfully printed, which accumulates into a total return value matching standard `printf` behavior.
3. **Edge Case Safety:**
   * `%s` safely catches `NULL` inputs and outputs `(null)`.
   * `%p` handles `NULL` pointers explicitly by printing `(nil)` under Linux/glibc standards instead of raw zero or incorrect strings. In the bonus, `(nil)` is treated like a string: width and `-` apply, while `0` and precision are ignored.
   * `%d`/`%i` converts standard integers to `long` types internally to prevent overflow errors when evaluating bounds like `INT_MIN`.
4. **Flag priority rules (bonus):**
   * `-` overrides `0`.
   * For integer conversions, a precision overrides `0`.
   * `+` overrides space.
   * `#` has no effect on the value `0`.
   * A precision of `0` with the value `0` prints no digits, as the real `printf` does.

---

## Instructions

### Compilation & Build

The project includes a Makefile with standard 42 rules. To compile the library (`libftprintf.a`) with the mandatory part, run:

```bash
make
```

To compile the library with the bonus part, run:

```bash
make bonus
```

### Available Makefile Rules:

* `make` — Compiles the mandatory source files and generates `libftprintf.a`.
* `make bonus` — Compiles the bonus source files and generates `libftprintf.a` with flags and width support.
* `make clean` — Removes object files (`.o`).
* `make fclean` — Removes object files and the compiled archive (`libftprintf.a`).
* `make re` — Re-compiles the entire project from scratch.

> Run `make fclean` before switching between `make` and `make bonus`, so objects of one part are not mixed with the other.

### Integration & Usage

To use `ft_printf` in your own C programs, include the header and link the archive during compilation:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s! Hex value: %x\n", "1337", 42);
    return (0);
}
```

### Bonus usage example

When built with `make bonus`, include the bonus header instead:

```c
#include "ft_printf_bonus.h"

int main(void)
{
    ft_printf("[%5d]\n", 42);        /* [   42] */
    ft_printf("[%-5d]\n", 42);       /* [42   ] */
    ft_printf("[%05d]\n", 42);       /* [00042] */
    ft_printf("[%+d]\n", 42);        /* [+42] */
    ft_printf("[% d]\n", 42);        /* [ 42] */
    ft_printf("[%.5d]\n", 42);       /* [00042] */
    ft_printf("[%#x]\n", 255);       /* [0xff] */
    ft_printf("[%10.3s]\n", "hello");/* [       hel] */
    ft_printf("[%8p]\n", NULL);      /* [   (nil)] */
    return (0);
}
```

Compile using:

```bash
make bonus
gcc -Wall -Wextra -Werror main.c libftprintf.a -o test_printf
```

---

## Resources & AI Usage


### 1: Resources:

* **C Standard Library Documentation:** Man pages for `stdarg(3)` and `printf(3)` (flags, field width and precision rules).

* **The Linux Programming Interface** (Michael Kerrisk) — System calls and formatting internals https://broman.dev/download/The%20Linux%20Programming%20Interface.pdf.

* **42 Common Core Norms:** Strict syntax, variable declaration limits, and scope management guidelines.

* **Variadic Functions in C (1):** https://www.geeksforgeeks.org/c/variadic-functions-in-c/

* **Variadic Functions in C (2):** https://coddy.tech/learn/courses/functions_in_c_/variadic_function

### 2: AI Usage Disclosure

AI was used as a conceptual reference to clarify low-level memory mechanics, and standard library specifications. For the bonus part, it was also used to help understand the behavior of flags, width and precision in the real `printf`.

All implementation logic, coding, and debugging were personally written and verified.
