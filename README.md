# RSA Implementation in C++

This project provides a simple yet effective implementation of the RSA encryption and decryption algorithm using C++. It's designed to showcase the fundamentals of RSA cryptography, including key generation, encryption, and decryption processes.

## Getting Started

### Prerequisites

Before running this project, ensure you have a C++ compiler installed on your system. This implementation does not require any special libraries or frameworks outside of the standard C++ library.

### Compilation

To compile the project, navigate to the project directory where `rsa.cpp` and `miller_rabin.cpp` are located. These two files must reside in the same folder since `rsa.cpp` includes and uses functionality from `miller_rabin.cpp` for primality testing.

Use the following command to compile the project (assuming you are using `g++`):

```bash
g++ -o rsa rsa.cpp miller_rabin.cpp
```

This command will compile the source files and generate an executable named rsa.

### Running the Program
To run the program, simply execute the generated executable in your terminal:

```bash
./rsa
```

### Note
- No special input arguments are required when executing the program. It is designed to request the necessary input (the message for encryption) directly from the user at the start.
- Ensure that both miller_rabin.cpp and rsa.cpp are located in the same directory to avoid compilation errors, as the RSA implementation relies on the Miller-Rabin primality test defined in miller_rabin.cpp.
