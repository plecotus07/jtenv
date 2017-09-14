// +++ -------------------------------------------------------------------------
#include "project_jtenv.hpp"
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
Project::Project (const std::string& aWsName, const std::string& aName, const fs::path& aPath) :
    m_wsName {aWsName},
    m_name {aName},
	m_fullName {},
    m_path {aPath},
    m_remoteGit {},
    m_git {},
    m_defaultBranch {"master"},
    m_cmakeCmds {}
{

}
// -----------------------------------------------------------------------------
bool Project::init (const std::string& aFullName, jkpp::Git::UPtr&& aRemoteGit)
{
	m_fullName = aFullName;
    m_remoteGit = std::move(aRemoteGit);

	try {
		fs::create_directories(m_path);
	} catch (...) {
		return false;
	}

	if (!save()) return false;

    std::ofstream file {(m_path / ".gitignore").string(), std::fstream::out};
    if (!file) return false;

    file << m_name + "_repo/\n";

    file.close();

    return true;
}
// -----------------------------------------------------------------------------
bool Project::load (jkpp::GitBuilder& aGitBuilder)
{
    if (!fs::exists(m_path / "project.conf")) return false;

    std::ifstream file {(m_path / "project.conf").string(), std::fstream::in};
    if (!file) return false;

    std::string line {};

    while (std::getline(file, line)) {
        if (!line.empty()) {
    		auto pos {line.find_first_of('=')};
            if (pos == std::string::npos) return false;

            std::string key {line.substr(0, pos)};
            std::string value {line.substr(pos + 1)};

            if (key == "repo_url") m_remoteGit = aGitBuilder.create(value);
            else if (key == "full_name") m_fullName = value;
            else if (key == "default_branch") m_defaultBranch = value;
			else if (key == "cmake_cmd") {
				auto ccnpos {value.find_first_of('|')};
				if (ccnpos == std::string::npos) return false;
                auto ccmpos {value.find_last_of('|')};
				if (ccmpos == std::string::npos) return false;

				std::string cc_name {value.substr(0, ccnpos)};
				std::string mode_str {value.substr(ccnpos + 1, ccmpos)};
				std::string cc_cmd {value.substr(ccmpos + 1)};

				if (cc_name.empty() || mode_str.empty() || cc_cmd.empty()) return false;
                CMakeMode cc_mode {getCMakeModeFromString(mode_str)};
                if (cc_mode == CMakeMode::invalid) return false;

				m_cmakeCmds.insert(std::make_pair(cc_name, std::make_pair(cc_mode, cc_cmd)));
			} else return false;
        }
    }

	if (fs::exists(m_path / (m_name + "_repo"))) {
		m_git = aGitBuilder.create((m_path / (m_name + "_repo")).string());
	}

	return true;
}
// -----------------------------------------------------------------------------
bool Project::save ()
{
	if (!fs::exists(m_path)) return false;

	std::ofstream file {(m_path / "project.conf").string(), std::fstream::out};
    if (!file) return false;

    file << "full_name=" << m_fullName << '\n';
    file << "repo_url=" << m_remoteGit->getUrl() << '\n';
    file << "default_branch=" << m_defaultBranch << '\n';

	for (auto cc : m_cmakeCmds) file << "cmake_cmd=" << cc.first << "|" << getStringFromCMakeMode(cc.second.first) << "|" << cc.second.second << '\n';

    file.close();

    return true;
}
// -----------------------------------------------------------------------------
bool Project::clone (const std::string& aUserName, const std::string& aUserEmail, const fs::path&)
{
	if (!m_remoteGit) return false;

	jkpp::Git::UPtr git {m_remoteGit->clone((m_path / (m_name + "_repo")).string(), false)};
    if (!git) return false;
    m_git = std::move(git);

    m_git->command("config user.name \"" + aUserName + "\"");
    m_git->command("config user.email \"" + aUserEmail + "\"");

    m_git->command("checkout " + m_defaultBranch);

	return true;
}
// -----------------------------------------------------------------------------
bool Project::clear (bool aForce, std::string& aDetails)
{
    if (!fs::exists(getPath())) return false;
    if (!fs::exists(getRepoPath())) return false;

    auto status {getStatus(aDetails)};

    if (status != jkpp::Git::Status::clean
        && status != jkpp::Git::Status::empty
        && !aForce) return false;

    aDetails.clear();

    try { fs::remove_all(getRepoPath()); } catch (...) { return false; }

    return true;
}
// -----------------------------------------------------------------------------
bool Project::git (const std::string& aCommand)
{
	if (!m_git) return false;

    return m_git->command(aCommand);
}
// -----------------------------------------------------------------------------
jkpp::Git::Status Project::getStatus (std::string& aStatusDetails) const
{
	if (!m_git) return jkpp::Git::Status::not_cloned;

    return m_git->getStatus(aStatusDetails);
}
// -----------------------------------------------------------------------------
void Project::setRemoteRepoUrl (const std::string& aUrl)
{
///\todo assert (m_remoteGit)
	m_remoteGit->setUrl(aUrl);
}
// -----------------------------------------------------------------------------
bool Project::addCMakeCmd (const std::string& aName, CMakeMode aMode, const std::string& aCmd)
{
	if (aName.empty() || aCmd.empty()) return false;

    auto found {m_cmakeCmds.find(aName)};
    if (found != m_cmakeCmds.end()) return false;

	m_cmakeCmds.insert(std::make_pair(aName, std::make_pair(aMode,aCmd)));

    return true;
}
// -----------------------------------------------------------------------------
bool Project::removeCMakeCmd (const std::string& aName)
{
	auto found (m_cmakeCmds.find(aName));
    if (found == m_cmakeCmds.end()) return false;

    m_cmakeCmds.erase(found);

    return true;
}
// -----------------------------------------------------------------------------
Project::CMakeCmd Project::getCMakeCmd (const std::string& aName) const
{
    auto found {m_cmakeCmds.find(aName)};
    if (found != m_cmakeCmds.end()) return std::make_pair(CMakeMode::invalid, std::string{});

    return found->second;
}
// -----------------------------------------------------------------------------
Project::CMakeMode Project::getCMakeModeFromString (const std::string aString)
{
	if (aString == "conf") return CMakeMode::conf;
    else if (aString == "build") return CMakeMode::build;

    return CMakeMode::invalid;
}
// -----------------------------------------------------------------------------
std::string Project::getStringFromCMakeMode (CMakeMode aMode)
{
	switch (aMode) {
    case CMakeMode::invalid: return std::string{};
        case CMakeMode::conf: return "conf";
        case CMakeMode::build: return "build";
    }
    return std::string{};
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
