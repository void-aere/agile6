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

### Feature Paradise

- Tab completion in functions that search and choose (see trie structure, [this link](https://github.com/scop/bash-completion)).
- Obfuscate typeface for passwords (see bash text decoration).
- Boxes with curved edges (see unicode Box Drawing block 256D, 256E).
- This thing: 🯁🯂🯃.

### Changelog

#### 241014-01

- DataHandler has been changed into a templated class, so it can be used for loading and saving data other than just bank accounts.
- This was done in preparation for the user account database, and the incorporation of both databases into a context class.