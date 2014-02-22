#include "Subscriber.h"

Subscriber::Subscriber(void)
:	myMailTypes(2)
{
}

Subscriber::~Subscriber()
{
	for(int i=0,count=myMailTypes.Count();i<count;i++)
	{
		PostMaster::GetInstance()->RemoveSubscriber(this,myMailTypes[i]);
	}
}

void Subscriber::SubscribeToMailType(const MailType& aMailType)
{
	PostMaster::GetInstance()->AddSubscriber(this,aMailType);
	myMailTypes.Add(aMailType);
}