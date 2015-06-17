# clpp
A thin header-only wrapper around OpenCL 2.0+ for modern and highlevel C++.

Usage
-----

- As this is a header-only library, just fork this project and set an apropriate
include path to its directory for compilation.
- Keep in mind that this project requires a C++14 conform compiler.
- Only include the root-level file "clpp.hpp" - this file controls the rest of the inclusion!

Dependencies
------------

The only depencendies so far are some header-only libraries from boost, namely:
- boost/algorithm/string/split.hpp
- boost/algorithm/string/classification.hpp
- boost/optional.hpp

Errors & Exceptions
-------------------

- Besides OpenCL handling error recovery with return codes this library wraps
these codes and has an exception type for every possible return code available
which you can catch.
- There is a super-exception type, namely cl::error::AnyError with which you can
catch any exception which is thrown by this library.
