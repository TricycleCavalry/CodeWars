#ifndef MAILING_LIST_HEADER
#define MAILING_LIST_HEADER

#include "GrowingArray.h"

class Mail;
class Subscriber;

class MailingList
{
public:
	MailingList(void);
	~MailingList(void);

	void AddSubscriber(Subscriber* aSubscriber);
	void RemoveSubscriber(Subscriber* aSubscriber);

	void DistributeMail(Mail& someMail);

private:
	GrowingArray<Subscriber*> mySubscribers;
};

#endif