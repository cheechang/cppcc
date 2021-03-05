#pragma once
#include<string>
const int MYSELF_FILE_ROOT_PID = 1;
const int SHARED_FILE_ROOT_PID = 2;
const int MYSELF_FILE_FILETYPE = 2;
const int SHARED_FILE_FILETYPE = 3;
const int MYSELF_FILE_ROLEID = 3;
const int SHARED_FILE_ROOT_ROLEID = 6;
const std::string MYSELF_FILE_ROOT_FILECODE = "10011001";
const std::string SHARED_FILE_ROOT_FILECODE = "10011002";
const long long MAX_FILE_LIMIT = 128 * 1024 * 1024;
enum FileType{
	ALL_FILE = 0,
	SELF_FILE = 1,
	SHARED_FILE
};
enum FolderType{
	TYPE_FILE=1,//普通文件
	TYPE_COMMON,//普通文件夹
	TYPE_TEAM, //团队文件夹
	TYPE_SPECIAL//特殊文件夹
};