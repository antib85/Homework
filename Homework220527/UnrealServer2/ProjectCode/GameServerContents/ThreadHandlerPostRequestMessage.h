#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
#include "ServerToClient.h"
#include "ContentsUserData.h"
#include <memory>

// �� ���ǵ� ���⼭ �޴´�.
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

	// �� �޼����� ó�� �޾����� �����ϴ� �Լ�
	void Start() override;

public:

private:
	void DBCheck();

	void ResultSend();

protected:
	ThreadHandlerPostRequestMessage& operator=(const ThreadHandlerPostRequestMessage& _Other) = delete;
	ThreadHandlerPostRequestMessage& operator=(ThreadHandlerPostRequestMessage&& _Other) = delete;

};

