# Unit Tests for fts-elastic

This directory contains unit tests for the fts-elastic plugin.

## Running Tests

### On Linux/macOS (with autotools):

After building the project:

```bash
cd test
make check
```

### On Windows or without autotools:

**Option 1: Direct compile (if gcc is available):**

Open Command Prompt (cmd.exe, not PowerShell):
```cmd
cd test
gcc -Wall -Wextra -std=c99 -o test-settings.exe test-settings.c
test-settings.exe
```

**Option 2: Use WSL (Windows Subsystem for Linux):**
```bash
cd test
gcc -Wall -Wextra -std=c99 -o test-settings test-settings.c
./test-settings
```

**Option 3: Use MSYS2/MinGW:**

Install MSYS2, then in MSYS2 terminal:
```bash
cd test
gcc -Wall -Wextra -std=c99 -o test-settings.exe test-settings.c
./test-settings.exe
```

**Note:** If you don't have gcc installed, you can:
- Install MinGW/MSYS2: https://www.msys2.org/
- Use WSL: `wsl --install`
- Or build on a Linux server

## Test Coverage

### Settings Parsing Tests

- `default_date_range` parsing:
  - Valid values: `1`, `1month`, `3`, `3months`, `6`, `6months`, `0`, `disabled`
  - Invalid values: `2`, `12`, etc. (should be rejected)

- `result_size_limit` parsing:
  - Valid values: Any positive integer (e.g., `10000`, `50000`, `100000`)
  - Invalid values: `0` or negative numbers (should be rejected)

## Adding New Tests

To add new tests:

1. Add test functions to `test-settings.c`
2. Call them from `main()`
3. Use the pattern: `if (test_function() != 0) { failures++; }`

## Future Test Ideas

- JSON query building validation
- Date filter logic
- Field name escaping
- Multi-field query optimization

