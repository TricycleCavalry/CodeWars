#ifndef SUBSCRIBER_HEADER
#define SUBSCRIBER_HEADER

#include "PostMaster.h"
#include "MailType.h"
class Mail;

class Subscriber
{
public:
	Subscriber(void);
	virtual ~Subscriber();

	void SubscribeToMailType(const MailType& aMailType);

	virtual void HandleMessage(Mail& aMail) = 0;
private:
	GrowingArray<MailType> myMailTypes;
};

#endif