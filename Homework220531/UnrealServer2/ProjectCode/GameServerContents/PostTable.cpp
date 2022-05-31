#include "PreCompile.h"
#include "PostTable.h"
#include <GameServerBase\GameServerThread.h>


//////////////////////////////////////////////////////////////////// 

PostTable_SelectIDToPostInfo::PostTable_SelectIDToPostInfo(std::string _ID)
	: DBQuery("SELECT Idx, ToNickName, Letters, FromNickName, PostTime FROM userver2.post WHERE ToNickName = ?")
	, ToNickName(_ID)
{
}

bool PostTable_SelectIDToPostInfo::DoQuery()
{
	// 이 방어를 위한 시맨틱을 만들어달라고 해야하는데.
	// 이 시맨틱은 이미 구조체로 제공됩니다.
	// 방어를 하겠다.
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindString(ToNickName);

	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();
	RowDatas.reserve(Row);


	while (Result->Next())
	{
		RowDatas.push_back(
			std::make_shared<PostRow>(PostRow(
				Result->GetInt(0),
				Result->GetString(1),
				Result->GetString(2),
				Result->GetString(3),
				Result->GetString(4)
			)
		)
		);
	}

	return true;
}

PostTable_SelectIDToUserInfo::PostTable_SelectIDToUserInfo(std::string _ID)
	: DBQuery("SELECT Idx, ToNickName, Letters, FromNickName, PostTime FROM userver2.post WHERE ToNickName = ?")
	, NickName(_ID)
	, RowData(nullptr)
{
}

bool PostTable_SelectIDToUserInfo::DoQuery()
{
	// 이 방어를 위한 시맨틱을 만들어달라고 해야하는데.
	// 이 시맨틱은 이미 구조체로 제공됩니다.
	// 방어를 하겠다.
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindString(NickName);

	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();

	if (0 == Result->AffectedRows())
	{
		return false;
	}

	if (false == Result->Next())
	{
		return false;
	}

	RowData = std::make_shared<PostRow>(Result->GetInt(0), Result->GetString(1), Result->GetString(2), Result->GetString(3), Result->GetString(4));
	return true;
}

//////////////////////////////////////////////////////////////////// 

PostTable_AllUserInfo::PostTable_AllUserInfo()
	: DBQuery("SELECT * FROM userver2.post")

{
}

bool PostTable_AllUserInfo::DoQuery()
{
	// 이 방어를 위한 시맨틱을 만들어달라고 해야하는데.
	// 이 시맨틱은 이미 구조체로 제공됩니다.
	// 방어를 하겠다.
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);
	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();
	RowDatas.reserve(Row);

	while (Result->Next())
	{
		RowDatas.push_back(std::make_shared<PostRow>(Result->GetInt(0), Result->GetString(1), Result->GetString(2), Result->GetString(3), Result->GetString(4)));
	}
	return true;
}

//////////////////////////////////////////////////////////////////// 

PostTable_InsertUserInfo::PostTable_InsertUserInfo(std::string _ID, std::string _Letters, std::string _FromNickName, std::string _PostTime)
	: DBQuery("INSERT INTO userver2.post (ToNickName, Letters, FromNickName, PostTime) VALUES (?, ?, ?, ?)")
	, ToNickName(_ID)
	, Letters(_Letters)
	, FromNickName(_FromNickName)
	, PostTime(_PostTime)
{
}

bool PostTable_InsertUserInfo::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindString(ToNickName);
	Stmt->ParamBindString(Letters);
	Stmt->ParamBindString(FromNickName);
	Stmt->ParamBindString(PostTime);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();
	uint64_t Id = Stmt->InsertId();

	if (-1 == Row)
	{
		return false;
	}

	return true;
}