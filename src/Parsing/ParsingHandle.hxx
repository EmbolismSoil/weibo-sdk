#ifndef PARSING_PARSINGHANDLE_HXX
#define PARSING_PARSINGHANDLE_HXX

#include <string>

namespace Json
{
	class Value;
}

namespace weibo
{
	/** Parsing handler 
	* 
	* @author welbon
	*
	* @date 2011-12-07
	*/
	class ParsingHandle
	{
	public:
		ParsingHandle(Json::Value* val = NULL, bool owner = false);
		virtual ~ParsingHandle();

		bool parse(const char* source);
		void reset(Json::Value* val, bool owner);
		const char* getErrorMessage() const;
		const char* getSource() const;
		Json::Value& getValue();

	protected:
		Json::Value* mValRoot;
		std::string mErrorMessage;
		std::string mSource;
		bool mIsOwner;
	};

}

#endif //PARSING_PARSINGHANDLE_HXX