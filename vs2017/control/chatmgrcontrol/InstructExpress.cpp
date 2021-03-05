#include "InstructExpress.h"
#include <log.h>
#include <regex>
#include "../utils/common.h"
#include "../utils/Error.h"
#include "GlobalDef.h"
std::map<std::string, std::string> InstructExpress::m_InstructMap;
std::map<std::string, std::string> InstructExpress::m_engInstructMap;
InstructExpress::InstructExpress()
{
}
InstructExpress::~InstructExpress()
{

}
void InstructExpress::init(){
	if ( !m_InstructMap.empty())
	{
		return;
	}
	if (!m_engInstructMap.empty())
	{
		return;
	}
	m_InstructMap.insert(std::pair<std::string, std::string>("[微笑]", "weixiao"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[色]", "se"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[得意]", "deyi"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[流泪]", "liulei"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[害羞]", "haixiu"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[闭嘴]", "bizui"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[睡]", "shui"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[尴尬]", "ganga"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[发怒]", "fanu"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[调皮]", "tiaopi"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[呲牙]", "ciya"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[惊讶]", "jingya"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[抓狂]", "zhuakuang"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[偷笑]", "touxiao"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[白眼]", "baiyan"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[傲慢]", "aoman"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[流汗]", "liuhan"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[疑问]", "yiwen"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[嘘]", "xu"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[晕]", "yun"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[疯了]", "fengle"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[敲打]", "qiaoda"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[衰]", "shuai"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[再见]", "zaijian"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[抠鼻]", "koubi"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[鼓掌]", "guzhang"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[坏笑]", "huaixiao"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[鄙视]", "bishi"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[委屈]", "weiqu"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[阴险]", "yinxian"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[亲亲]", "qinqin"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[可怜]", "kelian"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[左哼哼]", "zuohengheng"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[右哼哼]", "youhengheng"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[不高兴]", "bugaoxing"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[挨打]", "aida"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[不屑]", "buxie"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[大笑]", "daxiao"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[哼]", "heng"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[花痴]", "huachi"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[哭]", "ku"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[困]", "kun"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[冷汗]", "lenghan"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[难过]", "nanguo"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[怒]", "nu"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[窃笑]", "qiexiao"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[吓]", "xia"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[折磨]", "zhemo"));

	m_engInstructMap.insert(std::pair<std::string, std::string>("[Smile]", "weixiao"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Drool]", "se"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Smug]", "deyi"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Tears]", "liulei"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Shy]", "haixiu"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Slience]", "bizui"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Sleep]", "shui"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Awkward]", "ganga"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Angry]", "fanu"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Naughty]", "tiaopi"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Grin]", "ciya"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Surprise]", "jingya"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Scream]", "zhuakuang"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Titter]", "touxiao"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Slight]", "baiyan"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Arrogant]", "aoman"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Speechless]", "liuhan"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Question]", "yiwen"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Hush]", "xu"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Dizzy]", "yun"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Crazy]", "fengle"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Hammer]", "qiaoda"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Unlucky]", "shuai"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Bye]", "zaijian"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[NosePick]", "koubi"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Applaud]", "guzhang"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Grin]", "huaixiao"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Disdain]", "bishi"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Grievance]", "weiqu"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Sly]", "yinxian"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Kiss]", "qinqin"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Pitiful]", "kelian"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[BahLeft]", "zuohengheng"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[BahRight]", "youhengheng"));
	m_engInstructMap.insert(std::pair<std::string, std::string>("[Unhappy]", "bugaoxing"));
	////带翻译
	m_InstructMap.insert(std::pair<std::string, std::string>("[Beating]", "aida"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[Scorn]", "buxie"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[Laughter]", "daxiao"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[Hummed]", "heng"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[Anthomaniac]", "huachi"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[Cry]", "ku"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[Tired]", "kun"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[ColdSweat]", "lenghan"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[Sad]", "nanguo"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[Rage]", "nu"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[qiexiao]", "qiexiao"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[xia]", "xia"));
	m_InstructMap.insert(std::pair<std::string, std::string>("[zhemo]", "zhemo"));
}
void InstructExpress::InstructParseTo(std::string src, std::string& target)
{
	/*
	1. 查找
	2. 找到后取出来字串
	3. 将字串拼成[e]fxxx[/e]
	4. 将拼成的字符串替换
	*/
	std::string		replace("");
	std::string		strUrl("");
	std::string		strDst("");
	std::string     strName("");
	char szUtf8[buffersize] = {0};
	std::string::const_iterator	it = src.begin();
	std::string::const_iterator	end = src.end();

	std::smatch	find;
	std::regex	regImage(EMOJI_REG);

	replace = src;

	std::string tempReplace = replace;
	//	查找字串
	while (std::regex_search(it, end, find, regImage))
	{
		it = find[0].second;
		//	提取字串
		std::string	strFind = find[1];
		strUrl = find[2];
		if (strUrl.empty())
		{
			continue;
		}

		//	获取文件名
		std::string::size_type pos = 0;
		pos = strUrl.rfind("/");
		if (pos!= std::string::npos)
		{
			strName = strUrl.substr(pos+1,strUrl.length());
			utils::string_replace(strName,".png","");
		}
		//	查找指令
		strDst = getInstruct(strName);
		if (strDst.empty()){
			continue;
		}
		//	替换字符串
		utils::string_replace(tempReplace,strFind,strDst);
	}
	replace = tempReplace;
	if (replace.empty())
	{
		return;
	}
	target = replace;
}
void InstructExpress::InstructParseFrom(std::string src, std::string& target)
{
	std::string	strPath("");
	std::string replace(src);
	std::regex	regInstruct("(\\[(.*?)\\])");

	strPath = ":/img/smilies/instruct/";
	std::string::const_iterator	it = src.begin();
	std::string::const_iterator	end = src.end();
	std::smatch	find;
	std::string strUrl("");

	while (std::regex_search(it, end, find, regInstruct))
	{
		it = find[0].second;
		std::string strM = find[1];
		std::string	strUrl(EMOJI_IMAGE);
		std::string	strName("");
		std::string	strFind("");

		strFind = find[1];
		if (strFind.empty())
		{
			continue;
		}
		strName = getExpression(strFind);
		if (strName.empty()){
			continue;
		}
		strUrl += strPath;
		strUrl += strName;
		strUrl += ".png";
		strUrl += EMOJI_IMAGE;

		//	替换字符串
		utils::string_replace(replace,strFind,strUrl);
	}
	if (replace.empty())
	{
		return;
	}
	target = replace;
}

std::string InstructExpress::getExpression(const std::string& instruct)
{
BEGIN;
	char szAnsi[1024*4] = { 0 };
#ifdef _WIN32
	utils::utf82char((char*)instruct.c_str(), szAnsi);
#else 
	strcpy(szAnsi,instruct.c_str());
#endif // _WIN32
	init();
	std::map<std::string, std::string>::iterator iter = m_InstructMap.find(szAnsi);
	if (iter != m_InstructMap.end()){
		AddLog(LOG_LEV_INFO,"ExpressionName=%s", iter->second.c_str());
		return iter->second;
	}
	std::map<std::string, std::string>::iterator iterEng = m_engInstructMap.find(szAnsi);
	if (iterEng != m_engInstructMap.end()){
		AddLog(LOG_LEV_INFO,"ExpressionName=%s", iterEng->second.c_str());
		return iterEng->second;
	}
	return "";
}
std::string InstructExpress::getInstruct(const std::string& expression)
{
BEGIN;
	std::string result("");
	init();
	std::map<std::string, std::string>::const_iterator iter;
	if (utils::Error::IsChinese())
	{
		for (iter = m_InstructMap.begin(); iter != m_InstructMap.end(); ++iter){
			if (iter->second != expression){
				continue;
			}
#ifdef _WIN32
			char szUtf8[1024 * 4] = { 0 };
			utils::char2utf8((char*)iter->first.c_str(), szUtf8);
			result = std::string(szUtf8);
#else
			result = iter->first;
#endif
			return result;
		}
	}
	else
	{
		for (iter = m_engInstructMap.begin(); iter != m_engInstructMap.end(); ++iter){
			if (iter->second != expression){
				continue;
			}
#ifdef _WIN32
			char szUtf8[1024 * 4] = { 0 };
			utils::char2utf8((char*)iter->first.c_str(), szUtf8);
			result = std::string(szUtf8);
#else
			result = iter->first;
#endif
			return result;
		}
	}
END;
	return result;
}

