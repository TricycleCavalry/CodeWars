#ifndef _BLOCK_ATTRIBUTE_BLOCKIN_H_
#define _BLOCK_ATTRIBUTE_BLOCKIN_H_
#include "blockattribute.h"

class BlockAttributeBlockin : public BlockAttribute
{
public:
	BlockAttributeBlockin(void);
	~BlockAttributeBlockin(void);

	void Init();

	void Clear();


protected:
	BlockAttribute* SubCopy();

};

#endif