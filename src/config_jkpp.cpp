// +++ -------------------------------------------------------------------------
#include "config_jkpp.hpp"
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<std::string>::setValue (const std::string& aValue)
{
	m_value = aValue;
	return true;
}
// -----------------------------------------------------------------------------
template <>
void ConfigFileFieldImpl<std::string>::clearValue ()
{
	m_value.clear();
}
// -----------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<int>::setValue (const std::string& aValue)
{
	try {
		m_value = std::stoi(aValue);
	} catch (...) {
		return false;
	}

	return true;
}
// -----------------------------------------------------------------------------
template <>
void ConfigFileFieldImpl<int>::clearValue ()
{
	m_value = 0;
}
// -----------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<double>::setValue (const std::string& aValue)
{
	try {
		m_value = std::stod(aValue);
	} catch (...) {
		return false;
	}

	return true;
}
// -----------------------------------------------------------------------------
template <>
void ConfigFileFieldImpl<double>::clearValue ()
{
	m_value = 0;
}
// -----------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<std::map<std::string, std::string>>::setValue (const std::string& aValue)
{
	auto sepPos = aValue.find_first_of(m_separator);
	if (sepPos == std::string::npos) return false;

	m_value.insert(std::make_pair(aValue.substr(0, sepPos), aValue.substr(sepPos + 1)));
	return true;
}
// +++ -------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<std::vector<std::string>>::setValue (const std::string& aValue)
{
	m_value.push_back(aValue);
	return true;
}
// -----------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<std::vector<int>>::setValue (const std::string& aValue)
{
	try {
		m_value.push_back(std::stoi(aValue));
	} catch (...) {
		return false;
	}

	return true;
}
// +++ -------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<std::vector<double>>::setValue (const std::string& aValue)
{
	try {
		m_value.push_back(std::stod(aValue));
	} catch (...) {
		return false;
	}

	return true;
}
// -----------------------------------------------------------------------------
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
		} catch (...) {
			return false;
		}
	}

	std::ofstream file {m_path.string(), std::ofstream::out};
	if (!file) return false;

	saveValues (file);

	file.close();
	return true;
}
// -----------------------------------------------------------------------------
void ConfigFile::setDefaultValues ()
{
	for (auto& field : m_fields) {
		field->setDefaultValue();
	}
}
// -----------------------------------------------------------------------------
bool ConfigFile::setValue (const std::string& aKey, const std::string& aValue)
{
	for (auto& field : m_fields)
		if (field->getKey() == aKey) return field->setValue(aValue);

	return false;
}
// -----------------------------------------------------------------------------
bool ConfigFile::saveValues (std::ofstream& aFileStream) const
{
	for (auto& field : m_fields)
		if (!field->saveValue(aFileStream)) {
			return false;
		}

	return true;
}
// -----------------------------------------------------------------------------
void ConfigFile::clearValues ()
{
	for (auto& field : m_fields)
		field->clearValue();
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
	} catch (...) {
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
