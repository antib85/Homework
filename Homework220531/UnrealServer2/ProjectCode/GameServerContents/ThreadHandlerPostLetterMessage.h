#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
#include "ServerToClient.h"
#include "ContentsUserData.h"
#include <memory>

// �� ���ǵ� ���⼭ �޴´�.
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

	// �� �޼����� ó�� �޾����� �����ϴ� �Լ�
	void Start() override;

public:

private:
	void DBCheck();

	void ResultSend();

protected:
	ThreadHandlerPostLetterMessage& operator=(const ThreadHandlerPostLetterMessage& _Other) = delete;
	ThreadHandlerPostLetterMessage& operator=(ThreadHandlerPostLetterMessage&& _Other) = delete;

};

