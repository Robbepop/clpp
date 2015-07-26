Improvements & Bug fixes:
- Property Lists implementation uses ugly C-style casts in the get and set methods.
- After thinking about why I should add this:
      -> Add convenience methods for command queue creation as Context::createDefaultQueue() etc.
- Replace Context constructors with old and memory leaking wrappers around function callback.

Experimental:
- Maybe add a CompileOptions class for an improved experience setting the compile and link options.
- Convert some templated RangeX algorithms to IteratorX algorithms:
	-> PartitionCapabilities constructor
	-> (maybe) Partition constructor

TODO:
- Implementation of CommandQueue:
    - read/write (rect) image functions
	- add all possible operations for ranges building on top of their iterator based counterparts.
- Complete API and implementation of several Image objects. E.g. Image2D, Image3D, Image1D etc...
- Implementation of Program:
    - clCreateProgramWithSource
        - Context::createProgramWithSource(file1, file2, ...); // variadic
    - clCreateProgramWithBinary
    - clCreateProgramWithBuiltInKernels
    - clCompileProgram
    - clLinkProgram
- Implementation of Kernel:
    - clSetKernelArgSVMPointer
        - add template specialization for Kernel::setArg(index, value);
    - clSetKernelExecInfo
        - Kernel::setSvmPointer(svm1, svm2, ...);
        - Kernel::useFineGrainSystem(flag);
- Complete API and implementation of KernelFunctor.
- Complete API and implementation of Sampler.
- Complete API and implementation of Pipe.
- Complete API and implementation of Shared Virtual Memory (SVM).
- Create overloadings for functions taking a callback without additional user_data parameter.

