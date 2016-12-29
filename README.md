* simple barrier implementation
	* ported from my local repository, pthread barrier in C
	* C++ std::thread
* constructor
	* Barrier(#thread, blocking)
		* blocking <= true
			* blocking barrier
			* every thread entering barrier blocked
		* blocking <= false
			* nonblocking barrier
			* one thread must reach this barrier (MASTER)
			* others check this (SLAVE), if true, MASTER reached here
	* BarrierNonBlocking, BarrierBlocking
		* just a function called "wait" or something
		* use proper one specified in constructor