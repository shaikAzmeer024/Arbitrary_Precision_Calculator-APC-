# 🧮 Arbitrary Precision Calculator in C

## 📌 Project Overview

A command-line **Arbitrary Precision Calculator (APC)** developed using **C and Data Structures** to perform arithmetic operations on very large numbers beyond the limits of standard C data types.

Large numbers are processed digit-by-digit using **linked-list based data structures**.

## 🚀 Features

- ➕ Addition
- ➖ Subtraction
- ✖️ Multiplication (`x` / `X`)
- ➗ Division
- 🔢 Supports very large numbers
- 🔗 Linked-list based number processing
- 💻 Command-line argument support
- ⚠️ Input and operator validation

## 🛠️ Technologies

- **Language:** C
- **Data Structure:** Doubly Linked List
- **Concepts:** Pointers, Dynamic Memory Allocation, Structures, Command Line Arguments
- **Compiler:** GCC
- **Platform:** Linux / WSL

## ▶️ Compilation

```bash
gcc *.c -o calculator
```

## ▶️ Usage

```bash
./calculator operand1 operator operand2
```

### Example

```bash
./calculator 12345678910111213141516171819 + 9876543210123456789
```

### Output

```text
Result : 12345678919987756351639628608
```

## 📌 Supported Operators

```text
+  Addition
-  Subtraction
x  Multiplication
X  Multiplication
/  Division
```

## 🎯 Learning Outcomes

- Implemented large-number arithmetic from scratch.
- Strengthened C programming and Data Structures skills.
- Practiced pointers and dynamic memory allocation.
- Implemented arithmetic operations using linked lists.
- Improved algorithmic and problem-solving skills.

## 👨‍💻 Author

**Shaik Azmeer**

*C Programming | Data Structures | Embedded Systems*
