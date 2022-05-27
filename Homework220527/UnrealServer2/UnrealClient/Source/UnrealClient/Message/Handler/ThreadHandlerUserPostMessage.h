#pragma once
#include "../ThreadHandlerBase.h"


// 그 세션도 여기서 받는다.
class ThreadHandlerUserPostMessage : public ThreadHandlerBase<UserPostMessage>
{
private: 


public: // Default
	void Start();
};

