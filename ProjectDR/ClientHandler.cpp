#include "StdAfx.h"
#include "ClientHandler.h"

ClientHandler* ClientHandler::m_pInstance = NULL; 

#pragma warning( disable : 4996 )

// receives data from the server
void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData);
// receives NatNet error messages
void __cdecl MessageHandler(int msgType, char* msg);

ClientHandler::ClientHandler(void) {
	this->natnet = 0;
	this->natNetServerRunning = false;
	
	this->optiTrackConnectionType = ConnectionType_Multicast;
	
	this->optiTrackServerCommandPort = 1510;
	this->optiTrackServerDataPort = 1511;

	this->setLocalIpAddress("127.0.0.1");
	this->setOptiTrackServerIpAddress("127.0.0.1");
	
	this->g_hMutex = CreateMutex(
		NULL,
		//(LPSECURITY_ATTRIBUTES)SYNCHRONIZE, 
		FALSE, 
		NULL);

	this->outputLogObject = NULL;
	this->outputLogFunction = NULL;

	this->initDataObject = NULL;
	this->initDataFunction = NULL;

	this->updateDataObject = NULL;
	this->updateDataFunction = NULL;
}


ClientHandler::~ClientHandler(void) {
	// Free the mutex
	CloseHandle(this->g_hMutex);
}

// Lock the client handler
bool ClientHandler::lock() {
	// Request ownership of mutex
	DWORD  dwWaitResult;
	while(true) {
		// Wait for Mutex to be free
		dwWaitResult = WaitForSingleObject(g_hMutex, INFINITE);
		switch (dwWaitResult) {
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0: 
			return true;
			break; 

			// The thread got ownership of an abandoned mutex
			// The database is in an indeterminate state
		case WAIT_ABANDONED: 
			return false; 
			break;
		}
	}

	return false;
}

int ClientHandler::connect() {
	int iResult;

	// A string buffer used to temporally store strings
	// for the output log.
	char buf[2048];

	if (this->outputLogFunction) {
		// Print Connection Information to the Output Log
		sprintf_s(buf, "Connecting to Server...\n");
		this->outputLogFunction(buf, outputLogObject);

		if (this->optiTrackConnectionType == ConnectionType_Unicast) {
			sprintf_s(buf, "Connection Type: Unicast\n");
			this->outputLogFunction(buf, outputLogObject);
		} else if (this->optiTrackConnectionType == ConnectionType_Multicast) {
			sprintf_s(buf, "Connection Type: Multicast\n");
			this->outputLogFunction(buf, outputLogObject);
		} else {
			sprintf_s(buf, "Connection Type: Unknown\n");
			this->outputLogFunction(buf, outputLogObject);
		}

		sprintf_s(buf, "Command port of server: %d\n", this->optiTrackServerCommandPort);
		this->outputLogFunction(buf, outputLogObject);

		sprintf_s(buf, "Data port of server: %d\n", this->optiTrackServerDataPort);
		this->outputLogFunction(buf, outputLogObject);

		sprintf_s(buf, "Connecting to server at %s...\n", this->otptiTrackServerIPAddress);
		this->outputLogFunction(buf, outputLogObject);

		sprintf_s(buf, "Connecting from %s...\n", this->localIPAddress);
		this->outputLogFunction(buf, outputLogObject);
	}

    // Create NatNet Client
    iResult = initClient();
	
	// Print any error messages
	if (this->outputLogFunction) {
		if(iResult != ErrorCode_OK) {
			sprintf_s(buf, "Error initializing client.  See log for details.  Exiting\n");
			this->outputLogFunction(buf, outputLogObject);
		} else {
			sprintf_s(buf, "Client initialized and ready.\n");
			this->outputLogFunction(buf, outputLogObject);
		}
	}

	// Exit due to error
	if(iResult != ErrorCode_OK)
		return 1;

	// Check if successful at retrieving the NatNetClient from
	// the ClientHandler.
	if (!this->natnet) {
		if (this->outputLogFunction) {
			sprintf_s(buf, "Failed to get client from client handler.\n");
			this->outputLogFunction(buf, outputLogObject);
		}
		return 1;
	}

	// send/receive test request
	if (this->outputLogFunction) {
		sprintf_s(buf, "Sending Test Request\n");
		this->outputLogFunction(buf, outputLogObject);
	}

	// Test Connection
	void* response;
	int nBytes;
	iResult = this->natnet->SendMessageAndWait("TestRequest", &response, &nBytes);

	sDataDescriptions* pDataDefs = NULL;
	int nBodies = this->natnet->GetDataDescriptions(&pDataDefs);
	if(!pDataDefs) {
		//return 1;
	} else {
		for(int i=0; i < pDataDefs->nDataDescriptions; i++) {
			if(pDataDefs->arrDataDescriptions[i].type == Descriptor_MarkerSet) {
				// MarkerSet
				//sMarkerSetDescription* pMS = pDataDefs->arrDataDescriptions[i].Data.MarkerSetDescription;
				//printf("MarkerSet Name : %s\n", pMS->szName);
			} else if(pDataDefs->arrDataDescriptions[i].type == Descriptor_RigidBody) {
				// RigidBody
				sRigidBodyDescription* pRB = pDataDefs->arrDataDescriptions[i].Data.RigidBodyDescription;

				RigidBody* body = new RigidBody();
				body->setID(pRB->ID);
				body->setName(pRB->szName);

				if (!this->addRigidBody(body->getID(), body))
					delete body;

			} else if(pDataDefs->arrDataDescriptions[i].type == Descriptor_Skeleton) {
				// Skeleton
				//for(int j=0; j < pSK->nRigidBodies; j++) {
				//sRigidBodyDescription* pRB = &pSK->RigidBodies[j];
			} else {
				// Unknown
			}
		}
	}

	if (this->outputLogFunction) {
		// Retrieve Data Descriptions from server
		sprintf_s(buf, "Requesting Data Descriptions...\n");
		this->outputLogFunction(buf, outputLogObject);

		if(!pDataDefs) {
			sprintf_s(buf, "Unable to retrieve Data Descriptions.\n");
			this->outputLogFunction(buf, outputLogObject);
			//return 1;
		} else {
			sprintf_s(buf, "Received %d Data Descriptions:\n", pDataDefs->nDataDescriptions );
			this->outputLogFunction(buf, outputLogObject);
			for(int i=0; i < pDataDefs->nDataDescriptions; i++) {
				printf("Data Description # %d (type=%d)\n", i, pDataDefs->arrDataDescriptions[i].type);
				if(pDataDefs->arrDataDescriptions[i].type == Descriptor_MarkerSet) {
					// MarkerSet
					sMarkerSetDescription* pMS = pDataDefs->arrDataDescriptions[i].Data.MarkerSetDescription;
					printf("MarkerSet Name : %s\n", pMS->szName);
					for(int i=0; i < pMS->nMarkers; i++)
						printf("%s\n", pMS->szMarkerNames[i]);

				} else if(pDataDefs->arrDataDescriptions[i].type == Descriptor_RigidBody) {
					// RigidBody
					sRigidBodyDescription* pRB = pDataDefs->arrDataDescriptions[i].Data.RigidBodyDescription;
					printf("RigidBody Name : %s\n", pRB->szName);
					printf("RigidBody ID : %d\n", pRB->ID);
					printf("RigidBody Parent ID : %d\n", pRB->parentID);
					printf("Parent Offset : %3.2f,%3.2f,%3.2f\n", pRB->offsetx, pRB->offsety, pRB->offsetz);

					RigidBody* body = new RigidBody();
					body->setID(pRB->ID);
					body->setName(pRB->szName);

					if (!this->addRigidBody(body->getID(), body))
						delete body;

				} else if(pDataDefs->arrDataDescriptions[i].type == Descriptor_Skeleton) {
					// Skeleton
					sSkeletonDescription* pSK = pDataDefs->arrDataDescriptions[i].Data.SkeletonDescription;
					printf("Skeleton Name : %s\n", pSK->szName);
					printf("Skeleton ID : %d\n", pSK->skeletonID);
					printf("RigidBody (Bone) Count : %d\n", pSK->nRigidBodies);
					for(int j=0; j < pSK->nRigidBodies; j++) {
						sRigidBodyDescription* pRB = &pSK->RigidBodies[j];
						printf("  RigidBody Name : %s\n", pRB->szName);
						printf("  RigidBody ID : %d\n", pRB->ID);
						printf("  RigidBody Parent ID : %d\n", pRB->parentID);
						printf("  Parent Offset : %3.2f,%3.2f,%3.2f\n", pRB->offsetx, pRB->offsety, pRB->offsetz);
					}
				} else {
					printf("Unknown data type.");
					// Unknown
				}
			}      
		}
	}

	// Set the Flag tell that the NatNetClient is connected
	// to a server to True.
	this->natNetServerRunning = true;

	// Ready to receive marker stream!
	if (this->outputLogFunction) {
		sprintf_s(buf, "Client is connected to server and listening for data...\n");
		this->outputLogFunction(buf, outputLogObject);
	}

	if (this->initDataFunction) {
		// Initialize the OptiTack Data
		initDataFunction(initDataObject);
	}

	// Return Error Code OK
	return ErrorCode_OK;
}

int ClientHandler::disconnect() {
	// Done - clean up.
	if (this->natnet) {
		if (this->outputLogFunction) {
			this->outputLogFunction("Disconnecting from Server...\n", outputLogObject);
		}

		// Disconnects from the server
		this->natnet->Uninitialize();

		if (this->outputLogFunction) {
			this->outputLogFunction("Client is Disconnected.\n", outputLogObject);
		}
	} else {
		if (this->outputLogFunction) {
			this->outputLogFunction("Client is already not connected to the server.\n", outputLogObject);
		}
	}

	this->natNetServerRunning = false;

	// Return Error Code OK
	return ErrorCode_OK;
}

// Establish a NatNet Client connection
int ClientHandler::initClient()
{
    // release previous server
    if(this->natnet != 0)
    {
        this->natnet->Uninitialize();
        delete natnet;
    }

    // create NatNet client
    this->natnet = new NatNetClient(optiTrackConnectionType);

	char buf[2048];

    // print version info
    unsigned char ver[4];
    this->natnet->NatNetVersion(ver);

	if (this->outputLogFunction) {
		sprintf_s(buf, "NatNet Client (NatNet ver. %d.%d.%d.%d)\n", ver[0], ver[1], ver[2], ver[3]);
		this->outputLogFunction(buf, outputLogObject);
	}

    // Set callback handlers
    this->natnet->SetMessageCallback(MessageHandler);
    this->natnet->SetVerbosityLevel(Verbosity_Debug);
    this->natnet->SetDataCallback( DataHandler, this );	// this function will receive data from the server

    // Init Client and connect to NatNet server
    // to use NatNet default port assignments
    // int retCode = (*theClient)->Initialize(szMyIPAddress, szServerIPAddress);
    // to use a different port for commands and/or data:
    int retCode = natnet->Initialize(this->localIPAddress, this->otptiTrackServerIPAddress, 
		this->optiTrackServerCommandPort, this->optiTrackServerDataPort);
    if (retCode != ErrorCode_OK) {
		if (this->outputLogFunction) {
			sprintf_s(buf, "Unable to connect to server.  Error code: %d. Exiting\n", retCode);
			this->outputLogFunction(buf, outputLogObject);
		}
        return ErrorCode_Internal;
    } else {
        // print server info
        sServerDescription ServerDescription;
        memset(&ServerDescription, 0, sizeof(ServerDescription));
        this->natnet->GetServerDescription(&ServerDescription);
        if(!ServerDescription.HostPresent) {
			if (this->outputLogFunction) {
				sprintf_s(buf, "Unable to connect to server. Host not present. Exiting.\n");
				this->outputLogFunction(buf, outputLogObject);
			}
            return 1;
        }

		if (this->outputLogFunction) {
			sprintf_s(buf, "\nServer application info:\n");
			this->outputLogFunction(buf, outputLogObject);

			sprintf_s(buf, "Application: %s (ver. %d.%d.%d.%d)\n", ServerDescription.szHostApp, ServerDescription.HostAppVersion[0],
				ServerDescription.HostAppVersion[1],ServerDescription.HostAppVersion[2],ServerDescription.HostAppVersion[3]);
			this->outputLogFunction(buf, outputLogObject);

			sprintf_s(buf, "NatNet Version: %d.%d.%d.%d\n", ServerDescription.NatNetVersion[0], ServerDescription.NatNetVersion[1],
				ServerDescription.NatNetVersion[2], ServerDescription.NatNetVersion[3]);
			this->outputLogFunction(buf, outputLogObject);

			sprintf_s(buf, "Client IP:%s\n", this->localIPAddress);
			this->outputLogFunction(buf, outputLogObject);

			sprintf_s(buf, "Server IP:%s\n", this->otptiTrackServerIPAddress);
			this->outputLogFunction(buf, outputLogObject);

			sprintf_s(buf, "Server Name:%s\n\n", ServerDescription.szHostComputerName);
			this->outputLogFunction(buf, outputLogObject);
		}
    }

    return ErrorCode_OK;
}

void ClientHandler::resetClient() {
	if (!this->natnet) {
		if (this->outputLogFunction)
			this->outputLogFunction("Failed to get client from client handler during reset.\n", outputLogObject);
		return;
	}

	int iSuccess;

	if (this->outputLogFunction)
		this->outputLogFunction("\nre-setting Client\n\n.", outputLogObject);

	iSuccess = this->natnet->Uninitialize();
	if(iSuccess != 0)
		if (this->outputLogFunction)
			this->outputLogFunction("error un-initting Client\n", outputLogObject);

	iSuccess = this->natnet->Initialize(this->localIPAddress, this->otptiTrackServerIPAddress);
	if(iSuccess != 0)
		if (this->outputLogFunction)
			this->outputLogFunction("error re-initting Client\n", outputLogObject);
}

#pragma unmanaged
// DataHandler receives data from the server
void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData) {
	// Cast user data as ClientHandler
	ClientHandler* pClient = (ClientHandler*) pUserData;

	// Lock the ClientHandler so data isn't changed
	// by another thread.
	if (!pClient->lock())
		return;

	// Unlock the ClientHandler
	pClient->unlock();

	// Rigid Bodies
	for(int i = 0; i < data->nRigidBodies; i++) {
		// Get pointer to Rigid Body
		RigidBody* body = pClient->getRigidBody(data->RigidBodies[i].ID);

		// Check if Rigid Body with the given ID exists
		if ( body ) {
			// Lock the ClientHandler so data isn't changed
			// by another thread.
			if (!pClient->lock())
				continue;

			// Update the Position and Orientation of the Rigid Body
			float x = -data->RigidBodies[i].x;
			float z = data->RigidBodies[i].y;
			float y = data->RigidBodies[i].z;

			float qx = -data->RigidBodies[i].qx;
			float qy = data->RigidBodies[i].qz;
			float qz = data->RigidBodies[i].qy;
			float qw = data->RigidBodies[i].qw;

			body->addFrame(Eigen::Vector3f(x, y, z),
					Eigen::Quaternionf(qx, qy, qz, qw));

			// Clear all the previous markers that were attached to the Rigid Body
			body->clearMarkers();

			// Gather all the Markers attached to the Rigid Body
			for(int iMarker = 0; iMarker < data->RigidBodies[i].nMarkers; iMarker++) {
				// Create a new marker
				Marker marker;

				// Get the information about the marker
				if(data->RigidBodies[i].MarkerIDs)
					marker.setID(data->RigidBodies[i].MarkerIDs[iMarker]);

				if(data->RigidBodies[i].Markers) {
					x = -data->RigidBodies[i].Markers[iMarker][0];
					z = data->RigidBodies[i].Markers[iMarker][1];
					y = data->RigidBodies[i].Markers[iMarker][2];

					marker.setPosition(Eigen::Vector3f(x, y, z));
				}

				// Add the marker to the Rigid Body
				body->addMarker(marker);
			}

			// Unlock the ClientHandler
			pClient->unlock();
		}
	}

	// Update the OptiTrack data
	pClient->updateData();

}

// MessageHandler receives NatNet error/debug messages
void __cdecl MessageHandler(int msgType, char* msg) {
	//printf("\n%s\n", msg);
}
#pragma managed

void ClientHandler::updateData() {
	if (this->updateDataFunction) {
		updateDataFunction(updateDataObject);
	}
}

// Add a Rigid Body to the ClientHandler
bool ClientHandler::addRigidBody(int id, RigidBody* rigidBody) {
	// Try to insert the Rigid Body
	std::pair<RigidBody_iterator,bool> ret;
	ret = this->rigidBodies.insert ( std::pair<int, RigidBody*>(id, rigidBody) );

	// Check if insertion was successful
	if (ret.second == false)
		return false;

	// If insertion was successful return true
	return true;
}

// Get Rigid Body based on ID
RigidBody* ClientHandler::getRigidBody(int id) {
	// Try to find the Rigid Body
	RigidBody_iterator ret;
	ret = this->rigidBodies.find(id);

	// If not found return NULL
	if ( ret == this->rigidBodies.end())
		return 0;

	// If found return the Rigid Body
	return ret->second;
}


// Return the map of all the Rigid Bodies
RigidBodyMap ClientHandler::getRigidBodyMap() {
	return this->rigidBodies;
}
