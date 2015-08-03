# clpp
A thin header-only wrapper around OpenCL 2.0+ for modern and highlevel C++.

Note
----

Supports OpenCL 1.1, 1.2 and 2.0.
This does not include vendor specific extensions!


How can I use this in my projects?
----------------------------------

- Clone this repo and only include the top-level "clpp.hpp" file into your project.
- Set correct include paths of this header-only library while compiling.
- Requires a C++14 standard conform compiler!


Dependencies
------------

The only depencendies so far are some header-only libraries from boost, namely:
- boost/algorithm/string/split.hpp
- boost/algorithm/string/classification.hpp
- boost/optional.hpp

These dependencies might get removed in the future!


Error Handling
--------------

- This wrapper has a built-in exception type for every possible OpenCL error code
and works entirely via C++ exception handling.
- It is possible to catch any exception thrown by this library via cl::error::AnyError.
- There is currently no other way of handling errors - this might change in the future!