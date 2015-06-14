Improvements & Bug fixes:
- Context Properties implementation uses ugly C-style casts in the get and set methods.
- Add convenience methods for context creation as Context::createBest() etc. based on
  the Context with the Device with the most compute units.
- Add convenience methods for command queue creation as Context::createDefaultQueue() etc.
- Extend detail::error's global_info_map for all possible RetCodes.
- Context's constructor with callback still requires 'new' keyword with current implementation.

Experimental:
- Use templates instead of ScalarType and FPType enums to coordinate calls for different OpenCL primitives.
  Problem with this approach may be that the methods parameter (template) must be known at compiler time
  instead of at runtime.
- Maybe add a CompileOptions class for an improved experience setting the compile and link options.
- Convert some templated RangeX algorithms to IteratorX algorithms:
	-> PartitionCapabilities constructor
	-> (maybe) Partition constructor

TODO:
- Implement global error info table with the new exceptions.
- Complete implementation of CommandQueue.
- Complete API and implementation of several Image objects. E.g. Image2D, Image3D, Image1D etc...
- Complete API and implementation of Program.
- Complete API and implementation of Kernel.
- Complete API and implementation of KernelFunctor.
- Complete API and implementation of Sampler.
- Complete API and implementation of Pipe.
- Complete API and implementation of Shared Virtual Memory (SVM).
- Create a complete wrapper API for clCompileProgram with included headers.
- Create a complete wrapper API for clLinkProgram with linked source libraries.
- Create some more overloading for clCreateProgramWithSource for multiple source files handling.
