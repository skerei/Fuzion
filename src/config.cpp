#include "config.h"

Config::Config (const char* name, const char* path)
{
	this->name = name;
	this->path = path;
}

bool DoesFileExist(pstring path, const char* file)
{
	DIR* dir;
	dirent* pdir;
	
	dir = opendir(path.c_str());
	
	while (pdir = readdir(dir))
	{
		if (pdir->d_type == DT_REG)
		{
			if (strcmp(pdir->d_name, file) == 0)
				return true;
		}
	}

	return false;
}



bool DoesDirectoryExist(pstring path, const char* directory)
{
	DIR* dir;
	dirent* pdir;
	
	dir = opendir(path.c_str());
	
	while (pdir = readdir(dir))
	{
		if (pdir->d_type == DT_DIR)
		{
			if (strcmp(pdir->d_name, directory) == 0)
				return true;
		}
	}

	return false;
}

bool DoesConform(pstring config_path)
{
	return DoesFileExist(config_path, (char*)"config.json");
}

char* Config::GetMainConfigFile()
{
	pstring path;
	path << this->path << "/config.json";

	return (char*)path.c_str();
}

std::vector<Config> GetConfigs (const char* directory)
{
	std::vector<Config> configs;
	
	DIR* dir;
	dirent* pdir;

	dir = opendir(directory);

	while (pdir = readdir(dir))
	{
		if (pdir->d_type == DT_DIR && strcmp(pdir->d_name, ".") != 0 && strcmp(pdir->d_name, "..") != 0)
		{
			pstring config_path;
			config_path << directory << "/" << pdir->d_name;
			
			if (DoesConform (config_path))
			{
				Config new_config (pdir->d_name, config_path.c_str());
				configs.push_back (new_config);
			}
		}
	}

	
	return configs;
}