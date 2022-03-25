#include "PreCompile.h"
#include "ThreadHandlerJoinMessage.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include "GameServerUser.h"
#include <GameServerNet\DBConnecter.h>
#include "UserTable.h"
#include <GameServerCore\DBQueue.h>
#include <GameServerCore\NetQueue.h>
#include <functional>

// DB�� �����ϴ���
// �����ϴ���
// ���������� ��� ��Ŷ�� ������ �ϱ���
// ���δ� �̾ȿ��� �������� �ϰ�
// ����� �ܺη� ��������� �ȵ˴ϴ�.

// ��� �̷��� �ϰ������ �����ϸ� ū�ϳ��ϴ�.
// �ܿ�� ���� �ƴ϶� �ڵ带 §����� �ǵ��� �ľ��ض�.
// ���� ��������� ���ϴ� �̴ϴ�.
ThreadHandlerJoinMessage::ThreadHandlerJoinMessage()
{

}

ThreadHandlerJoinMessage::~ThreadHandlerJoinMessage()
{

}

void ThreadHandlerJoinMessage::Start()
{
	if (nullptr == TCPSession_)
	{
		GameServerDebug::LogError("Join TCPSession Error");
	}

	JoinResult_.Code = EGameServerCode::JoinError;
	DBWork(&ThreadHandlerJoinMessage::DBCheck); 
}

void ThreadHandlerJoinMessage::DBCheck(/*GameEngineThread* _Thread*/)
{
	UserTable_SelectIDToUserInfo SelectQuery(Message_->ID);
	SelectQuery.DoQuery();

	if (nullptr != SelectQuery.RowData)
	{
		JoinResult_.Code = EGameServerCode::JoinError;
	}
	else
	{
		JoinResult_.Code = EGameServerCode::OK;

		UserTable_InsertUserInfo Query = UserTable_InsertUserInfo(Message_->ID, Message_->PW);
		if (false == Query.DoQuery())
		{
			int a = 0;
		}
	}	

	NetWork(&ThreadHandlerJoinMessage::ResultSend);
}

void ThreadHandlerJoinMessage::ResultSend()
{
	std::shared_ptr<GameServerUser> NewUser = std::make_shared<GameServerUser>();
	GameServerString::UTF8ToAnsi(Message_->ID, NewUser->ID);

	TCPSession_->SetLink(NewUser);

	GameServerSerializer Sr;
	JoinResult_.Serialize(Sr);
	TCPSession_->Send(Sr.GetData());

	GameServerDebug::LogInfo("Join Result Out");
}