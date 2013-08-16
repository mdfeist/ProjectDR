#include "stdafx.h"
#include "KinectFusionRender.h"

#include "KinectFusion.h"
#include "ClientHandler.h"
#include "RigidBody.h"

KinectFusionRender::KinectFusionRender(void) : ImageRender() 
{
	fusion = new CKinectFusion();;
}

KinectFusionRender::~KinectFusionRender(void)
{
	if(fusion)
		delete fusion;
}


void KinectFusionRender::init() 
{ 
	ImageRender::init();
	fusion->SetImageData(data); 

	// Look for a connected Kinect, and create it if found
	HRESULT hr = fusion->CreateFirstConnected();	
	if (FAILED(hr))
	{
		fusion->SetInitializeError(true);
	}

	if (!fusion->GetInitializeError())
	{
		hr = fusion->InitializeKinectFusion();
		if(FAILED(hr))
		{
			fusion->SetInitializeError(true);
		}
	}
}

void KinectFusionRender::render(Camera* camera) 
{
	fusion->Update(); 

	ImageRender::render(camera); 
}