
// CODESTYLE: v2.0

// CommunicationDevice.cpp
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: lets an owner of this class communicate with the main game class through messages

#include "CommunicationDevice.h"

namespace ENGINE
{
	CommunicationDevice::CommunicationDevice(void* owner) :
		owner_(owner)
	{
		// implement class constructor here
	} // end constructor

	CommunicationDevice::~CommunicationDevice()
	{
		// implement class destructor here
	} // end destructor
	
	// get the owner of the communication device
	void* CommunicationDevice::GetOwner()
	{
		return owner_;
	}
		
	// handles the creation of an instance of this class
	CommunicationDevice* CommunicationDevice::Create(void* owner)
	{
		return new CommunicationDevice(owner);
	}
	
	// handles the memory release of an instance of this class
	void CommunicationDevice::Destroy(CommunicationDevice* deviceInstance)
	{
		if (0 != deviceInstance)
		{
			delete deviceInstance;
			deviceInstance = 0;
		}
	}

} // end namespace


