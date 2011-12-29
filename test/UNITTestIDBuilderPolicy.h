#ifndef WEIBOUNITTEST_UNITTESTIDBUILDERPOLICY_H
#define WEIBOUNITTEST_UNITTESTIDBUILDERPOLICY_H

#include <list>
#include <IWeiboDef.hxx>
#include "WeiboTestCaseHelper.h"

enum eRandomIDType
{
	RIT_STATUS,
	RIT_USERS,
	RIT_COMMENT,
	RIT_DIRECT_MESSAGE,
	RIT_FAVORITE,
	RIT_FAVORITE_TAG,
	RIT_TREND,
	RIT_TAG,
	RIT_RESULT,
};

class UNITTestIDBuilderPolicy
{
public:
	UNITTestIDBuilderPolicy(boost::shared_ptr<WeiboTestCaseHelper> helper, const eRandomIDType idType, 
                            unsigned int optionId = 0, const int counts = 1, const char* forkey = NULL);
    
	const char* asChar();
	const char* asWords();
	weibo::ID& asID();
    
	std::string getDateString();
	void getCommentIDAndStatuseID(std::string& commentId, std::string& statusId);
    
protected:
	template <typename T>
	void findResultFromHelpeListTemplate(unsigned int resultType, const int counts, std::string& outstring)
	{
		if (!mHelperPtr)
		{
			assert(false);
			return ;
		}
        
		WeiboTestCaseResultPtr result = mHelperPtr->checkoutReqResult(resultType);
		if (!result)
		{
			//assert(false);
			outstring = "1234567890";
			return ;
		}
        
		using namespace weibo;
		typedef ParsingList< T > ParsingListTemplate;
		boost::shared_ptr<ParsingListTemplate> templatePtr = boost::shared_dynamic_cast<ParsingListTemplate>(result->pasringPtr_);
		if (!templatePtr)
		{
			//assert(false);
			outstring = "1234567890";
			return ;
		}
        
        typename ParsingListTemplate::TParsingList::iterator it = templatePtr->mDataList.begin();
		int i = 0;
        
		while (it != templatePtr->mDataList.end() && i < counts)
		{
			if (!outstring.empty())
			{
				outstring += ",";
			}
            
			//outstring += findID<ParsingListTemplate::TDataPtr>(*it, (const eRandomIDType)mIdType);
			outstring += (*it)->getID();
            
			++ i;
			++ it;
		}
	}
    
	// Sample template
	template <typename T>
	void findResultFromHelpeSampleTemplate(const eRandomIDType idType, unsigned int resultType, std::string& outstring)
	{
		// Not implements
	}
    
	template <typename T>
	const char* findID(T type, const eRandomIDType idType)
	{
		switch(idType)
		{
            case RIT_STATUS:
            case RIT_COMMENT:
            case RIT_DIRECT_MESSAGE:
            case RIT_USERS:
			{
				//if (type && !type->id.empty())
				//{
				//	return type->getID();
				//}
			}
                break;
                
            case RIT_FAVORITE:
			{
				if (type)
				{
				}
			}
                break;
                
            case RIT_RESULT:
			{
				//if (type && !mKey.empty())
				//{
				//	T::ResultMap::iterator it = type->_resultMap.find(mKey.c_str());
				//	if (it != type->_resultMap.end())
				//	{
				//		return it->c_str();
				//	}
				//}
			}
                break;
                
            default:
                break;
		}
		return "";
	}
    
protected:
	boost::shared_ptr<WeiboTestCaseHelper> mHelperPtr;
	std::string mString;
	std::string mWords;
	std::string mKey;
	weibo::ID mID;
	eRandomIDType mIdType; 
};

#endif //WEIBOUNITTEST_UNITTESTIDBUILDERPOLICY_H
