#pragma once
#include "stdafx.h"

#include <string>

namespace FormEvents
{
	void showError(const std::string& msg);

	std::string getSpecialFolderMyDocuments();
	void getFilePath(std::string& pathBuffer);
	void getFilePath(std::string& pathBuffer, const std::string& defaultPath);

	bool propt(const std::string& title, const std::string& msg);
};

