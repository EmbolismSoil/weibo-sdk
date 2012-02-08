#ifndef WEIBOSDK_SDKIMPLHELPER_HXX
#define WEIBOSDK_SDKIMPLHELPER_HXX

#include <string>
#include "SDKRequest.hxx"

namespace weibo
{
	enum ParamAttr
	{
		ParamNormal			= 0x00000000,		//!< The parameter is a normal parameter.
		//!  This means that the parameter's value contains the file path
		//!  and the file specified by the file path is uploaded when the HTTP UPLOAD is started.
		ParamEncodedName  	= 0x00000002,		//!< The parameter's name needed to a URL-Encoded string.
		//!  This means that the parameter's name is not encoded using URL-encoding
		//!  before sending to the web server when the HTTP GET or POST is started.
		ParamEncodedValue	= 0x00000004,		//!< The parameter's value needed to a URL-Encoded string
		//!  This means that the parameter's value is not encoded using URL-encoding
		//!  before sending to the web server when the HTTP GET or POST is started.
		ParamEncoded 		= (ParamEncodedName| ParamEncodedValue),	//!< The parameter's name and value are URL-Encoded strings.
		//!  This means that the parameter's name and value are not encoded using URL-encoding
		//!  before sending to the web server when the HTTP GET or POST is started.
		/*/< 这个参数需要 UTF8编码**/
		ParamUTF8Name       = 0x0000008,

		ParamUTF8Value      = 0x0000010 /***/
	};

#define PARAM_ENCODE_UTF8 (ParamEncodedValue|ParamUTF8Value)

	/** Weibo internal implements helper.
	* 
	* @author welbon
	*
	* @date 2011-08-23
	*/
	class SDKHelper
	{
	public:
		static void getMethodURLFromOption(unsigned int methodOption, std::string &baseURL);
		static int convertEngineErrorToSDKError(const int code);

		/** Param setting function */
		static void setParam(char* param, const char *paramname, const char *paramval, int paramformat);
		static void setIntParam(char* param, const char * paramName, const long long paramval, bool forceAdd = false);

		/** Split string */
		static void split(std::vector<std::string>& outVector, const char* string, const char splite);

		static WeiboRequestPtr makeRequest(unsigned int methodOption, char *addtionParam, const eWeiboRequestFormat reqformat
			, const httpengine::HttpMethod iMethod, const char* appkey, const char* accessToken, const UserTaskInfo* pTask = NULL);

		static void makeRequestURL(std::string &outURL, std::string &outParam, const char* baseURL
			, bool isPost, const char* appkey, const char* accessToken);

		static void makeIDParams(char *outParam, const int length, const ID *usrId);
		static void makeVariableParams(char *outParam, const int length, VariableParams* var);
	};
}

#endif //WEIBOSDK_WEIBOIMPLHELPER_HXX