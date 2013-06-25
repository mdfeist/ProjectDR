#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <process.h>

#include <map>

#include "RigidBody.h"

#include "NatNetSDK\include\NatNetTypes.h"
#include "NatNetSDK\include\NatNetClient.h"

typedef std::map<int, RigidBody*> RigidBodyMap;
typedef RigidBodyMap::iterator RigidBody_iterator;

class ClientHandler
{
public:
	static ClientHandler* getInstance() {
		if(!m_pInstance) m_pInstance = new ClientHandler();
		return m_pInstance;
	}

	int connect();
	int disconnect();

	// Lock the client so data cannot be changed while doing updates
	bool lock();

	// Unlocks the client allowing threads to change its data
	void unlock() { ReleaseMutex(g_hMutex); }

	// Checks if the client is still connected to the server
	bool isNatNetServerRunning() { return this->natNetServerRunning; }

	// Setters/Getters for OptiTrack settings
	// Your local Ip Address
	void setLocalIpAddress(const char *ip) { strncpy_s(this->localIPAddress, 128, ip, 128); }
	void getLocalIpAddress(char *ip) { strncpy_s(ip, 128, this->localIPAddress, 128); }

	// The OptiTrack servers Ip Address
	void setOptiTrackServerIpAddress(const char *ip) { strncpy_s(this->otptiTrackServerIPAddress, 128, ip, 128); }
	void getOptiTrackServerIpAddress(char *ip) { strncpy_s(ip, 128, this->otptiTrackServerIPAddress, 128); }

	// The Data port of the OptiTrack server
	void setOptiTrackServerDataPort(unsigned int port) { this->optiTrackServerDataPort = port; }
	int getOptiTrackServerDataPort() { return this->optiTrackServerDataPort; }

	// The Command port of the OptiTrack server
	void setOptiTrackServerCommandPort(unsigned int port) { this->optiTrackServerCommandPort = port; }
	int getOptiTrackServerCommandPort() { return this->optiTrackServerCommandPort; }

	// The Connection Type of the OptiTrack server
	void setOptiTrackServerConnectionType(int type) { this->optiTrackConnectionType = type; }
	int getOptiTrackServerConnectionType() { return this->optiTrackConnectionType; }

	// Add a RigidBody to the ClientHandler
	bool addRigidBody(int id, RigidBody* rigidBody);
	// Get RigidBody based on it's id
	RigidBody* getRigidBody(int id);
	// Get all RigidBody's in a map
	RigidBodyMap getRigidBodyMap();

	// Callback Functions
	void setOutputLogCallback(void (*functionPtr)(const std::string&, void*), void* object) {
		outputLogObject = object;
		outputLogFunction = functionPtr;
	}

protected:
	ClientHandler(void);
	~ClientHandler(void);
private:
	ClientHandler(ClientHandler const&);
	ClientHandler& operator=(ClientHandler const&);

	static ClientHandler* m_pInstance;

	// Mutex used to lock the ClientHandler.
	// Allowing multiple threads to read/write data without errors.
	HANDLE g_hMutex;

	// Pointer to NatNetClient
	NatNetClient* natnet;
	// Used to see if the NatNetClient is connected to a server
	bool natNetServerRunning;
	// A map to store all the attached Rigid Bodies
	RigidBodyMap rigidBodies;

	// OptiTrack Server Settings 
	char localIPAddress[128];					// Your local IP Address
	char otptiTrackServerIPAddress[128];		// The OptiTrack servers Ip Address

	unsigned int optiTrackServerDataPort;		// The Data port of the OptiTrack server
	unsigned int optiTrackServerCommandPort;	// The Command port of the OptiTrack server

	int optiTrackConnectionType;				// The Connection Type of the OptiTrack server

	// Establish a NatNet Client connection
	int initClient();
	// Resets the NatNet Client connection
	void resetClient();

	// Callback Functions
	void *outputLogObject;
	void (*outputLogFunction)( const std::string&, void* );
};

