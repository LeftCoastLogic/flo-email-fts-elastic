# Building and Running Tests

## On Linux/macOS

If you have autotools installed:

```bash
./autogen.sh
./configure --with-dovecot=/usr/lib/dovecot/
make
cd test
make check
```

## On Windows

### Option 1: Use WSL (Windows Subsystem for Linux)

1. Install WSL and Ubuntu
2. Install autotools:
   ```bash
   sudo apt-get update
   sudo apt-get install autoconf automake libtool
   ```
3. Build and test:
   ```bash
   ./autogen.sh
   ./configure --with-dovecot=/usr/lib/dovecot/
   make
   cd test
   make check
   ```

### Option 2: Build on Linux Server

1. Copy source code to Linux server
2. Run autogen.sh and configure there
3. Copy back the built files if needed

### Option 3: Compile Test Directly (Simple Tests Only)

For simple unit tests like `test-settings.c`, you can compile directly without autotools:

```bash
cd test
gcc -Wall -Wextra -o test-settings test-settings.c
./test-settings
```

Or on Windows with MinGW/MSYS2:

```bash
cd test
gcc -Wall -Wextra -o test-settings.exe test-settings.c
./test-settings.exe
```

## Dependencies

- **For autotools build**: autoconf >= 2.52, automake, libtool
- **For direct compile**: gcc or clang
- **For full plugin build**: Dovecot development headers, json-c library

## Troubleshooting

### "Unable to locate GNU Autoconf"

- Install autotools: `sudo apt-get install autoconf automake libtool`
- Or use WSL on Windows
- Or compile test directly without autotools

### "configure: error: cannot find dovecot"

- Install Dovecot development package: `sudo apt-get install dovecot-dev`
- Or specify path: `./configure --with-dovecot=/path/to/dovecot`

