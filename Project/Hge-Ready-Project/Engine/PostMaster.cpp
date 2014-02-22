#include "PostMaster.h"

#include "Mail.h"
#include "Subscriber.h"
#include "Debug.h"

PostMaster* PostMaster::myInstance = NULL;

PostMaster::PostMaster(void)
{
}

PostMaster::~PostMaster(void)
{
}

void PostMaster::Create()
{
	if(myInstance != NULL)
	{
		DL_ASSERT("PostMaster: Instance already created.");
	}

	myInstance = new PostMaster();
}

void PostMaster::Destroy()
{
	if(myInstance == NULL)
	{
		DL_ASSERT("PostMaster: Instance is already NULL.");
	}

	delete myInstance;
}

PostMaster* PostMaster::GetInstance()
{
	return myInstance;
}

void PostMaster::AddMail(Mail& someMail)
{
	myMailList[someMail.myMailType].DistributeMail(someMail);
}

void PostMaster::AddSubscriber(Subscriber* aSubscriber, MailType aMailType)
{
	myMailList[aMailType].AddSubscriber(aSubscriber);
}

void PostMaster::RemoveSubscriber(Subscriber* aSubscriber, MailType aMailType)
{
	myMailList[aMailType].RemoveSubscriber(aSubscriber);
}

void PostMaster::SetIsStillFlag(bool aFlag)
{
	//myIsStillFlag = aFlag;
}

void PostMaster::SetFlagTrue()
{
	myIsStillFlag = true;
}

void PostMaster::SetFlagFalse()
{
	myIsStillFlag = false;
}