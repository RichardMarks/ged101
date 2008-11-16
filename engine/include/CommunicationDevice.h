
// CODESTYLE: v2.0

// CommunicationDevice.h
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: lets an owner of this class communicate with the main game class through messages

#ifndef __COMMUNICATIONDEVICE_H__
#define __COMMUNICATIONDEVICE_H__

namespace ENGINE
{
	class CommunicationDevice
	{
	public:
		// public members should be declared here

		// class constructor
		CommunicationDevice(void* owner);
		
		// class destructor
		~CommunicationDevice();

		// get the owner of the communication device
		void* GetOwner();

		// handles the creation of an instance of this class
		static CommunicationDevice* Create(void* owner);
		
		// handles the memory release of an instance of this class
		static void Destroy(CommunicationDevice* deviceInstance);
		
	private:
		// private members should be declared here
		void* owner_;
	}; // end class

} // end namespace
#endif


