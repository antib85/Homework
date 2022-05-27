#include "PreCompile.h"
#include "ThreadHandlerPostLetterMessage.h"
#include "ContentsSystemEnum.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include <GameServerNet\DBConnecter.h>
#include <GameServerNet\RedisConnecter.h>
#include "UserTable.h"
#include "CharacterTable.h"
#include "PostTable.h"
#include <GameServerCore\DBQueue.h>
#include <functional>
#include <GameServerCore\NetQueue.h>
#include <GameServerCore\GameServerSectionManager.h>
#include "ContentsUserData.h"

// DB에 접속하는일
// 검증하는일
// 마지막으로 결과 패킷을 보내는 일까지
// 전부다 이안에서 벌어져야 하고
// 절대로 외부로 새어나가서는 안됩니다.

// 모든 이렇게 하겠지라고 착각하면 큰일납니다.
// 외우는 것이 아니라 코드를 짠사람의 의도를 파악해라.
// 보통 경력자한테 원하는 겁니다.

// 레퍼런스 카운트는 항상 1인 상태야.
ThreadHandlerPostLetterMessage::ThreadHandlerPostLetterMessage()
{

}

ThreadHandlerPostLetterMessage::~ThreadHandlerPostLetterMessage()
{

}

void ThreadHandlerPostLetterMessage::Start()
{
	if (nullptr == Session_)
	{
		GameServerDebug::LogError("Login TCPSession Error");
	}

	DBWork(&ThreadHandlerPostLetterMessage::DBCheck);
}

void ThreadHandlerPostLetterMessage::DBCheck(/*GameEngineThread* _Thread*/)
{
	std::shared_ptr<ContentsUserData> Ptr = Session_->GetLink<ContentsUserData>(EDataIndex::USERDATA);

	PostTable_SelectIDToUserInfo ToNickQuery = PostTable_SelectIDToUserInfo(Message_->ToNickName);
	PostTable_SelectIDToUserInfo FromNickQuery = PostTable_SelectIDToUserInfo(Message_->FromNickName);

	if (false != ToNickQuery.DoQuery() && false != FromNickQuery.DoQuery())
	{
		if (Message_->ToNickName == Message_->FromNickName)
			return;

		PostTable_InsertUserInfo Insert = PostTable_InsertUserInfo(Message_->ToNickName, Message_->Letters, Message_->FromNickName);
	
		if (false != Insert.DoQuery())
		{
		
		}
	}
	

	

	//NetWork(&ThreadHandlerPostLetterMessage::ResultSend);
}

void ThreadHandlerPostLetterMessage::ResultSend()
{
	//GameServerSerializer Sr;
	//Result_.Serialize(Sr);
	//Session_->Send(Sr.GetData());

}

