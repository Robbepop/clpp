Improvements & Bug fixes:
- Context Properties implementation uses ugly C-style casts in the get and set methods.
- Add convenience methods for context creation as Context::createBest() etc. based on
  the Context with the Device with the most compute units.
- Add convenience methods for command queue creation as Context::createDefaultQueue() etc.
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
    - add Context::createDefault();
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
    - clGetKernelArgInfo: Kernel::getArg(index) -> KernelArg;
        - KernelArg::getAddressQualifier() -> AddressQualifier;
        - KernelArg::getAccessQualifier() -> AccessQualifier;
        - KernelArg::getTypeName() -> std::string;
        - KernelArg::getTypeQualifier() -> TypeQualifier;
        - KernelArg::getName() -> std::string;
    - clGetKernelWorkGroupInfo: Kernel::getWorkGroup(device?*) -> WorkGroup; // *optional parameter
        - WorkGroup::getGlobalWorkSize() -> NDRange<3>;
		- WorkGroup::getWorkGroupSize() -> size_t;
        - WorkGroup::getCompileWorkGroupSize() -> NDRange<3>;
        - WorkGroup::getLocalMemorySize() -> cl_ulong;
        - WorkGroup::getPreferredWorkGroupSizeMultiple() -> size_t;
        - WorkGroup::getPrivateMemorySize() -> cl_ulong;
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

