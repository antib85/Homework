#include <iostream>
#include <string>
#include <regex>

class GameServerString
{
public:
	static void Replace(std::string& _Text, const std::string& _Prev, const std::string& _Next, int _Count = 1)
	{
		for (int i = 0; i < _Count; i++)
		{
			if (_Text.find(_Prev) == std::string::npos)
				return;

			std::regex rx(_Prev);

			std::regex_replace(_Text, rx, _Next, std::regex_constants::format_first_only);

			_Text = std::regex_replace(_Text, rx, _Next, std::regex_constants::format_first_only);
		}
	}

	static void Insert(std::string& _Text, int _Index, const std::string& _InsertText)
	{
		if (_Text.size() < _Index)
			return;

		_Text.insert(_Index, _InsertText);
	}

	static void Remove(std::string& _Text, const std::string& _DeleteText)
	{
		if(_Text.find(_DeleteText) == std::string::npos)
			return;

		while (_Text.find(_DeleteText) != std::string::npos)
		{
			_Text = _Text.erase(_Text.find(_DeleteText), _DeleteText.size());
		}
	}

	static void TrimRemove(std::string& _Text)
	{
		_Text.erase(std::remove(_Text.begin(), _Text.end(), ' '), _Text.end());
	}

	static void ToUpper(std::string& _Text)
	{
		for (size_t i = 0; i < _Text.size(); i++)
		{
			_Text[i] = std::toupper(_Text[i]);
		}
	}
};

int main()
{
		std::string text = "안녕하세요 어떠신가요?? 5555ㅁ aaㅁa5555aaaa";

		GameServerString::Replace(text, "5555", "444", 2);
		std::cout << "Replace : " << text << std::endl;

		GameServerString::Insert(text, 10," 오늘은");
		std::cout << "Insert : " << text << std::endl;

		GameServerString::Remove(text, "ㅁ");
		std::cout << "Remove : " << text << std::endl;

		GameServerString::TrimRemove(text);
		std::cout << "TrimRemove : " << text << std::endl;

		GameServerString::ToUpper(text);
		std::cout << "ToUpper : " << text << std::endl;

		int a = 0;
}