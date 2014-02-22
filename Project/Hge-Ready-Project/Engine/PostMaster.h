#ifndef POST_MASTER_HEADER
#define POST_MASTER_HEADER

#include "MailType.h"
#include "MailingList.h"
#include "StaticArray.h"

class Mail;
class Subscriber;

class PostMaster
{
public:
	static void Create();
	static void Destroy();

	static PostMaster* GetInstance();

	void AddMail(Mail& someMail);
	
	void AddSubscriber(Subscriber* aSubscriber, MailType aMailType);
	void RemoveSubscriber(Subscriber* aSubscriber, MailType aMailType);

	static void SetIsStillFlag(bool aFlag);
	void SetFlagTrue();
	void SetFlagFalse();

	bool myIsStillFlag;
	
private:
	PostMaster(void);
	~PostMaster(void);

	static PostMaster* myInstance;

	StaticArray<MailingList, MAILTYPE_NR_OF_TYPES> myMailList;

};

#endif