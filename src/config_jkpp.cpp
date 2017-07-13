// +++ -------------------------------------------------------------------------
#include "config_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
ConfigFile::ConfigFile (const fs::path& aFilePath) : m_path{aFilePath}
{
}
// -----------------------------------------------------------------------------
bool ConfigFile::load ()
{
	if (!fs::exists(m_path)) {
		setDefaultValues();
		return save();
	}

	clearValues();

	std::ifstream file {m_path.string(), std::ifstream::in};
	if (!file) return false;
	std::vector<std::string> lines;
	std::string line {};
	while (std::getline(file, line)) lines.push_back(line);
	bool result {file.eof()};
	file.close();
	if (!result) return false;

	for (auto line : lines) {
		auto equalSignPos {line.find_first_of("=")};
		std::string key {line.substr(0, equalSignPos)};
		std::string value {line.substr(equalSignPos + 1)};
		if (!setValue(key, value)) return false;
	}

	return true;
}
// -----------------------------------------------------------------------------
bool ConfigFile::save () const
{
	if (!fs::exists(m_path.parent_path())) {
		try {
			fs::create_directories(m_path.parent_path());
		}
		catch (...) {
			return false;
		}
	}

	std::ofstream file {m_path.string(), std::ofstream::out};
	if (!file) return false;

	saveValues (file);

	file.close();
	return true;
}
// +++ -------------------------------------------------------------------------
Config::Config (const fs::path& aConfigDirPath) : m_configDirPath {aConfigDirPath}
{
}
// -----------------------------------------------------------------------------
bool Config::load ()
{
	if (!fs::exists(m_configDirPath)) {
		setDefaults();
		return save();
	}

	for (auto& file : m_configFiles)
		if (!file->load()) return false;
	return true;
}
// -----------------------------------------------------------------------------
bool Config::save() const
{
	try {
		if ((!fs::exists(m_configDirPath))
		        && (!fs::create_directory(m_configDirPath))) return false;
	}
	catch (...) {
		return false;
	}

	for (auto& file : m_configFiles) {
		if (!file->save()) return false;
	}
	return true;
}
// -----------------------------------------------------------------------------
void Config::setDefaults()
{
	for (auto& file : m_configFiles) file->setDefaultValues();
}
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
