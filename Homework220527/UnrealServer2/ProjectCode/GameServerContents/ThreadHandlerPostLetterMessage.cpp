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

// DB�� �����ϴ���
// �����ϴ���
// ���������� ��� ��Ŷ�� ������ �ϱ���
// ���δ� �̾ȿ��� �������� �ϰ�
// ����� �ܺη� ��������� �ȵ˴ϴ�.

// ��� �̷��� �ϰ������ �����ϸ� ū�ϳ��ϴ�.
// �ܿ�� ���� �ƴ϶� �ڵ带 §����� �ǵ��� �ľ��ض�.
// ���� ��������� ���ϴ� �̴ϴ�.

// ���۷��� ī��Ʈ�� �׻� 1�� ���¾�.
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

