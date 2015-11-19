# Overview #
This project is used for the Sina weibo's third-party application network request library,Please read follow document before you start use it.<br>
<a href='http://open.weibo.com/wiki/API%E6%96%87%E6%A1%A3_V2'>http://open.weibo.com/wiki/API%E6%96%87%E6%A1%A3_V2</a><br>

<h1>Requirement</h1>

<h2>Default IDE support</h2>
1. WIN32(VS2008)<br>
2. Mac OS or iOS(XCode)<br>
3. Unix/Linux(Automake)<br>

<h2>Require library</h2>
1. Boost<br>
2. LibCurl<br>
3. SSL<br>
4. CPPUnit (For UnitTest, if don't need Unittest, please ignore) <br>
<br>
<br>

<h1>Using weibo SDK</h1>
<br>
<pre><code><br>
#include &lt;weibo/IWeibo.hxx&gt;<br>
#include &lt;weibo/IWeiboMethod.hxx&gt;<br>
<br>
using namespace weibo;<br>
<br>
boost::shared_ptr&lt;weibo::IWeibo&gt; weiboPtr;<br>
static bool logined = false;<br>
<br>
void OnDelegateComplated(unsigned int methodOption, const char* httpHeader,<br>
						 ParsingObject* result, const UserTaskInfo* pTask);<br>
void OnDelegateErrored(unsigned int methodOption, const int errCode, const int subErrCode, <br>
					   ParsingObject* result, const UserTaskInfo* pTask);<br>
void OnDelegateWillRelease(unsigned int methodOption, const UserTaskInfo* pTask);<br>
<br>
void main()<br>
{<br>
	weiboPtr = weibo::WeiboFactory::getWeibo();<br>
	weiboPtr-&gt;startup();<br>
	<br>
	weibo::IWeiboMethod* method = weiboPtr-&gt;getMethod();<br>
<br>
	// Please assin your consumer key and consumer secret<br>
	weiboPtr-&gt;setOption(weibo::WOPT_CONSUMER, "YOUR CONSUMER KEY", "YOUR CONSUMER SECRET");<br>
<br>
	// Ansy request login, see OnDelegateComplated<br>
	method-&gt;oauth2("userName", "password", NULL);<br>
<br>
<br>
	// Delegate option<br>
	weiboPtr-&gt;OnDelegateComplated = &amp;OnDelegateComplated;<br>
	weiboPtr-&gt;OnDelegateErrored = &amp;OnDelegateErrored;<br>
	//weiboPtr-&gt;OnDelegateWillRelease = OnDelegateWillRelease;<br>
<br>
	// Must waiting for a moment.<br>
	Sleep(5000);<br>
<br>
	// Go! Send weibo, Especially, text  MUST convert to UTF8 when it is UNICODE character set.<br>
	method-&gt;postStatusesUpdate("This is a weibo.....", NULL, NULL);<br>
<br>
	// Must waiting for a moment.<br>
	Sleep(5000);<br>
<br>
	weiboPtr-&gt;stopAll();<br>
	weiboPtr-&gt;shutdown();<br>
<br>
	return 0;<br>
};<br>
<br>
<br>
void OnDelegateComplated(unsigned int methodOption, const char* httpHeader,<br>
						 ParsingObject* result, const UserTaskInfo* pTask)<br>
{<br>
	if (methodOption == WBOPT_OAUTH2_ACCESS_TOKEN) <br>
	{<br>
		if (result-&gt;isUseable())<br>
		{<br>
			logined = true;<br>
			std::string access_token = result-&gt;getSubStringByKey("access_token");<br>
<br>
			// Note: Must set acess token to sdk!<br>
			weiboPtr-&gt;setOption(WOPT_ACCESS_TOKEN, access_token.c_str());<br>
		}<br>
	}<br>
	else if (methodOption == WBOPT_POST_STATUSES_UPDATE)<br>
	{<br>
		// Send weibo successed!<br>
		// ...<br>
	}<br>
}<br>
<br>
void OnDelegateErrored(unsigned int methodOption, const int errCode, const int subErrCode, <br>
	  ParsingObject* result, const UserTaskInfo* pTask)<br>
{<br>
	// Please reference http://open.weibo.com/wiki/Help/error<br>
	if (methodOption == WBOPT_OAUTH2_ACCESS_TOKEN) <br>
	{<br>
		if (result &amp;&amp; result-&gt;isUseable())<br>
		{<br>
			std::string error_code = result-&gt;getSubStringByKey("error_code");<br>
			std::string request = result-&gt;getSubStringByKey("request");<br>
			std::string error = result-&gt;getSubStringByKey("error");<br>
		}<br>
	}<br>
	else if (methodOption == WBOPT_POST_STATUSES_UPDATE)<br>
	{<br>
		// Send weibo failed!<br>
		// ...<br>
	}<br>
}<br>
<br>
</code></pre>

<h1>Q&A</h1>
If you have any question, or any suggestion, please mail to me.<br>
chenchao@staff.sina.com.cn or chengang4@staff.sina.com.cn