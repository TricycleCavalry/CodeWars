#include "MailingList.h"

#include "Mail.h"
#include "Subscriber.h"

MailingList::MailingList(void)
:	mySubscribers(4)
{
}

MailingList::~MailingList(void)
{
}

void MailingList::AddSubscriber(Subscriber *aSubscriber)
{
	mySubscribers.Add(aSubscriber);
}

void MailingList::RemoveSubscriber(Subscriber *aSubscriber)
{
	mySubscribers.RemoveCyclic(aSubscriber);
}

void MailingList::DistributeMail(Mail &someMail)
{
	for(int i = 0; i < mySubscribers.Count(); i++)
	{
		mySubscribers[i]->HandleMessage(someMail);
	}
}
