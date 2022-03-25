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

// DB에 접속하는일
// 검증하는일
// 마지막으로 결과 패킷을 보내는 일까지
// 전부다 이안에서 벌어져야 하고
// 절대로 외부로 새어나가서는 안됩니다.

// 모든 이렇게 하겠지라고 착각하면 큰일납니다.
// 외우는 것이 아니라 코드를 짠사람의 의도를 파악해라.
// 보통 경력자한테 원하는 겁니다.
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