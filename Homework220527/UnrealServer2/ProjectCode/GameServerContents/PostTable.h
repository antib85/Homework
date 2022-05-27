#pragma once
#include <GameServerNet\DBQuery.h>
#include "ContentsStructure.h"

class PostRow : public std::enable_shared_from_this<PostRow>
{
public:
	union {
		struct
		{
			int			Index;
			std::string ToNickName;
			std::string Letters;
			std::string FromNickName;
		};
		FPostData PostData;
	};

public:
	PostRow(
		int _Index,
		std::string _ToNickName,
		std::string _Letters,
		std::string _FromNickName
	)
		:Index(_Index),
		ToNickName(_ToNickName),
		Letters(_Letters),
		FromNickName(_FromNickName)
	{
	}

	PostRow(
		const PostRow& _Data
	)
		:Index(_Data.Index),
		ToNickName(_Data.ToNickName),
		Letters(_Data.Letters),
		FromNickName(_Data.FromNickName)
	{
	}

	PostRow(
		const FPostData& _Data
	) : PostData(_Data)
	{
	}

	~PostRow()
	{
	}
};

class PostTable_SelectIDToPostInfo : public DBQuery
{
public:
	std::string ToNickName;
	std::vector<std::shared_ptr<PostRow>> RowDatas;

public:
	PostTable_SelectIDToPostInfo(std::string _ID);
	bool DoQuery() override;
};

class PostTable_SelectIDToUserInfo : public DBQuery
{
public:
	std::string NickName;
	std::shared_ptr<PostRow> RowData;

	FPostData ConvertInfoCharacter()
	{
		FPostData Data;

		Data.Index = RowData->Index;
		Data.ToNickName = RowData->ToNickName;
		Data.Letters = RowData->Letters;
		Data.FromNickName = RowData->FromNickName;
	}

public:
	PostTable_SelectIDToUserInfo(std::string _ID);
	bool DoQuery() override;
};

class PostTable_AllUserInfo : public DBQuery
{
public:
	std::vector<std::shared_ptr<PostRow>> RowDatas;

public:
	PostTable_AllUserInfo();

	bool DoQuery() override;
};

class PostTable_InsertUserInfo : public DBQuery
{
	std::string ToNickName;
	std::string Letters;
	std::string FromNickName;

public:
	PostTable_InsertUserInfo(std::string _ID, std::string _Letters, std::string _FromNickName);

	bool DoQuery() override;
};