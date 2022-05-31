#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
#include "ServerToClient.h"
#include "ContentsUserData.h"
#include <memory>

// 그 세션도 여기서 받는다.
class PostRow;
class ThreadHandlerPostLetterMessage final
	: public ThreadHandlerBase<PostLetterMessage>
{
private: // Member Var

public: // Default
	ThreadHandlerPostLetterMessage();
	~ThreadHandlerPostLetterMessage();
	ThreadHandlerPostLetterMessage(const ThreadHandlerPostLetterMessage& _Other) = delete;
	ThreadHandlerPostLetterMessage(ThreadHandlerPostLetterMessage&& _Other) noexcept = delete;

	// 이 메세지를 처음 받았을때 실행하는 함수
	void Start() override;

public:

private:
	void DBCheck();

	void ResultSend();

protected:
	ThreadHandlerPostLetterMessage& operator=(const ThreadHandlerPostLetterMessage& _Other) = delete;
	ThreadHandlerPostLetterMessage& operator=(ThreadHandlerPostLetterMessage&& _Other) = delete;

};

