Improvements & Bug fixes:
- Exceptions what() method is screwed and throws logical_error instead of providing information.
- Context Properties implementation uses ugly C-style casts in the get and set methods.
- Add convenience methods for context creation as Context::createBest() etc. based on
  the Context with the Device with the most compute units.
- Add convenience methods for command queue creation as Context::createDefaultQueue() etc.
- Fix bug that detail::Object's retain and release methods can't check for errors via detail::error::handle method.
- Extend detail::error's global_info_map for all possible RetCodes.
- Context's constructor with callback still requires 'new' keyword with current implementation.

Experimental:
- Use templates instead of ScalarType and FPType enums to coordinate calls for different OpenCL primitives.
  Problem with this approach may be that the methods parameter (template) must be known at compiler time
  instead of at runtime.
- Add several more ExceptionType's to this wrapper's API similar to JavaCL's exception type.
  Basically one ExceptionType for every error based RetCode. Would make RetCode storage in exception useless.
- Add when() method to CommandQueue which takes an EventRange and propagates it to any available
  CommandQueue operation to allow asynchronous operations waiting for events.
- Add Event::wait() method as variadic template to allow taking any amount of Event objects
  and automatically wait for them. E.g. Event::wait(event1, event2, event3);
  Same behaviour could be implemented for CommandQueue's when(), barrier() and marker() method.
- Maybe add a CompileOptions class for an improved experience setting the compile and link options.
- Convert some templated RangeX algorithms to IteratorX algorithms:
	-> PartitionCapabilities constructor
	-> (maybe) Partition constructor

TODO:
- Remove old exceptions from existing code.
- Implement global error info table with the new exceptions.
- Complete implementation of CommandQueue.
- Complete API and implementation of several Image objects. E.g. Image2D, Image3D, Image1D etc...
- Complete API and implementation of Program.
- Complete API and implementation of Kernel.
- Complete API and implementation of KernelFunctor.
- Complete API and implementation of Sampler.
- Complete API and implementation of Pipe.
- Complete API and implementation of Shared Virtual Memory (SVM).
- Create a complete wrapper API for clCompileProgram with included headers
- Create a complete wrapper API for clLinkProgram with linked source libraries
