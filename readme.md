## agile6

### Building the Project

1. Navigate to the root (this) directory.
2. Run `make`. Object files will be placed in the build directory.
3. To run the program, use `./output`. The executable is `build/output`, but there will be a symlink in this directory.

Note: `make clean` removes all compiler output.

### Best Practices for Git

- Don't stage your `.vscode` or other environment-specific files for commit.
- Don't commit anything compiled (`make clean` before staging)
- Don't push a version that doesn't compile.
- Try not to commit on the main branch.