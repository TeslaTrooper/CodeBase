#ifndef INTERNAL_LOGIC
#define INTERNAL_LOGIC

struct InternalLogic {


	/*
		Virtual destructor for proper cleanup of sub classes, which are
		implementing this interface.
	*/
	virtual ~InternalLogic() {}


	/*
		Calling this method will perform an entire update in terms of program logic.

		@param dt	defines the time since last frame.
	*/
	virtual void update(const float dt) = 0;

};

#endif INTERNAL_LOGIC