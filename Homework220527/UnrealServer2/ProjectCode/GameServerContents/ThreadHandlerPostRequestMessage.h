#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
#include "ServerToClient.h"
#include "ContentsUserData.h"
#include <memory>

// 그 세션도 여기서 받는다.
class ThreadHandlerPostRequestMessage final
	: public ThreadHandlerBase<PostRequestMessage>
{
private: // Member Var
	UserPostMessage Result_;

public: // Default
	ThreadHandlerPostRequestMessage();
	~ThreadHandlerPostRequestMessage();
	ThreadHandlerPostRequestMessage(const ThreadHandlerPostRequestMessage& _Other) = delete;
	ThreadHandlerPostRequestMessage(ThreadHandlerPostRequestMessage&& _Other) noexcept = delete;

	// 이 메세지를 처음 받았을때 실행하는 함수
	void Start() override;

public:

private:
	void DBCheck();

	void ResultSend();

protected:
	ThreadHandlerPostRequestMessage& operator=(const ThreadHandlerPostRequestMessage& _Other) = delete;
	ThreadHandlerPostRequestMessage& operator=(ThreadHandlerPostRequestMessage&& _Other) = delete;

};

