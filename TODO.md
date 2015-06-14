Improvements & Bug fixes:
- Context Properties implementation uses ugly C-style casts in the get and set methods.
- Add convenience methods for context creation as Context::createBest() etc. based on
  the Context with the Device with the most compute units.
- Add convenience methods for command queue creation as Context::createDefaultQueue() etc.
- Extend detail::error's global_info_map for all possible RetCodes.
- Context's constructor with callback still requires 'new' keyword with current implementation.

Experimental:
- Maybe add a CompileOptions class for an improved experience setting the compile and link options.
- Convert some templated RangeX algorithms to IteratorX algorithms:
	-> PartitionCapabilities constructor
	-> (maybe) Partition constructor

TODO:
- Implement global error info table with the new exceptions.
- Implementation of Context:
    - replace current constructors with named constructors.
    - add constructors without a properties parameter:
        - Context::createForDevices(device1, device2, ...); // may also take only one argument
        - Context::createForDevices(deviceRange);
        - Context::createForType(deviceType);
    - add Context::createBest() named constructor which constructs the Context with
      the device with the most compute units.
- Implementation of CommandQueue:
    - read/write (rect) image functions
- Complete API and implementation of several Image objects. E.g. Image2D, Image3D, Image1D etc...
- Implementation of Program:
    - clCreateProgramWithBinary
    - clCreateProgramWithBuiltInKernels
    - clCompileProgram
    - clLinkProgram
- Implementation of Kernel:
    - clGetKernelArgInfo
    - clGetKernelWorkGroupInfo
    - clSetKernelArgSVMPointer
    - clSetKernelExecInfo
- Complete API and implementation of KernelFunctor.
- Complete API and implementation of Sampler.
- Complete API and implementation of Pipe.
- Complete API and implementation of Shared Virtual Memory (SVM).
- Create some more overloading for clCreateProgramWithSource for multiple source files handling.
- Create overloadings for functions taking a callback without additional user_data parameter.

