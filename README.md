# My_Assembler_Project
# My Assembler Project - Two-Pass Assembler

## Overview

This project is a two-pass assembler for a simple computer system. The assembler reads assembly code and converts it to machine code through three main steps:

1. **Pre-Assembly**: Handle macros and check for basic errors
2. **Two-Pass Assembly**:
   - **First Pass**: Find all labels and assign memory addresses
   - **Second Pass**: Create the final machine code

## Pre-Assembly Stage

Before the main assembly process, the program handles macros and does basic checks.

### What it does:
- **Finds Macros**: Looks for macro definitions (starting with `macro` and ending with `endmacro`)
- **Expands Macros**: Replaces macro calls with the actual macro code
- **Creates New File**: Makes a new file (`.am`) with all macros expanded

### Error Checking:
- Makes sure macros are properly closed with `endmacro`
- Checks that macro names don't conflict with assembly commands
- Prevents defining the same macro twice
- Validates macro syntax

### Common Errors Found:
- Missing `endmacro` at the end of a macro
- Using reserved words as macro names
- Trying to define a macro that already exists
- Wrong macro syntax

### Output:
- **Expanded File (`.am`)**: Assembly code with all macros replaced by their content

## First Pass

The first pass reads through the expanded code to build a table of all labels and their addresses.

### Main Tasks:
- **Find Labels**: Identifies all labels in the code
- **Assign Addresses**: Gives each label a memory address
- **Count Memory**: Keeps track of how much memory is needed for instructions and data

### What it tracks:
- **Instruction Counter (IC)**: Counts memory used by commands
- **Data Counter (DC)**: Counts memory used by data
- **Symbol Table**: A list matching labels to their addresses

### Errors it finds:
- Labels that are used but never defined
- The same label defined more than once
- Wrong syntax in assembly commands
- Problems with memory allocation

### Output:
- **Symbol Table**: Complete list of labels and their memory addresses
- **Memory Info**: How much memory is needed for the next pass

## Second Pass

The second pass uses the symbol table to create the final machine code.

### What it does:
- **Convert Instructions**: Turns assembly commands into binary code
- **Resolve Labels**: Replaces label names with their actual addresses
- **Handle Data**: Processes data declarations and numbers

### Reference Handling:
- **Internal Labels**: Labels defined in this program
- **External Labels**: Labels from other programs
- **Entry Points**: Labels that other programs can use

### Errors it catches:
- Wrong addressing modes for instructions
- Invalid operands or parameters
- Labels that can't be resolved
- Incorrect instruction formats

## Output Files

When assembly is successful, these files are created:

### 1. Object File (`.ob`)
- Contains the final machine code in binary format
- Includes both instructions and data
- Ready to be loaded and run

### 2. External File (`.ext`)
- Lists external labels used in the program
- Shows where each external reference appears
- Needed for linking with other programs

### 3. Entry File (`.ent`)
- Lists labels that other programs can access
- Shows the address of each entry point
- Defines what this program makes available to others

### 4. Error Messages
- Clear error descriptions with line numbers
- Explains what went wrong and where
- Helps fix problems in the code

## How to Use

```bash
./project [filename1] [filename2] ... [filenameN]
```

**Note**: Don't include the `.as` extension when typing the filename - the program adds it automatically.

## Key Features

- **Good Error Reporting**: Finds and explains errors clearly
- **Memory Management**: Efficiently uses available memory
- **Clean Design**: Each stage does its job separately
- **Easy to Extend**: Code is organized and easy to modify

## Technical Details

- **Programming Language**: Written in C
- **Memory Size**: 256 words of RAM, each word is 10 bits
- **Address Space**: Instructions and data share the same memory
- **File Types**: Reads `.as` files, creates `.ob`, `.ext`, and `.ent` files

## Testing

The project includes tests for:
- Different types of assembly programs
- Macro processing edge cases
- Various error conditions
- Memory limit testing
- Output file format checking

## Development Info

- **Platform**: Works on Linux systems
- **Compiler**: Uses GCC with standard C
- **Build**: Simple Makefile included
- **Requirements**: Only standard C libraries needed

