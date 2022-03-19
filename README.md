# FOMOD-Creation-Tool
Repository of old versions of the tool available on Nexus.  Recently updated to compile with a modern compiler.

## Instructions

* Get C++Builder Community Edition from https://www.embarcadero.com/products/cbuilder/starter
* Compiles with no warnings on the Clang based compilers for 32/64 bits

## Plans
* File I/O is currently handled using C funtions as opposed to C++ methods.  I want to work on that.
* Perhaps porting the XML handling to a convenient open source library
* Port to .NET/mono so that it can be cross platform.  Currently uses the C++Builder VCL
