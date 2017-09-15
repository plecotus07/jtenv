// +++ -------------------------------------------------------------------------
#include "project_jtenv.hpp"
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
    m_customCmds {}
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
			else if (key == "custom_cmd") {
				auto ccnpos {value.find_first_of('|')};
				if (ccnpos == std::string::npos) return false;
                auto ccmpos {value.find_last_of('|')};
				if (ccmpos == std::string::npos) return false;

				std::string cc_name {value.substr(0, ccnpos)};
				std::string cc_dir {value.substr(ccnpos + 1, ccmpos - ccnpos - 1)};
				std::string cc_cmd {value.substr(ccmpos + 1)};

				if (cc_name.empty() || cc_dir.empty() || cc_cmd.empty()) return false;

				m_customCmds.insert(std::make_pair(cc_name, std::make_pair(cc_dir, cc_cmd)));
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

	for (auto cc : m_customCmds) file << "custom_cmd=" << cc.first << "|" << cc.second.first << "|" << cc.second.second << '\n';

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
bool Project::addCustomCmd (const std::string& aName, const std::string& aDir, const std::string& aCmd)
{
	if (aName.empty() || aDir.empty() ||aCmd.empty()) return false;

    auto found {m_customCmds.find(aName)};
    if (found != m_customCmds.end()) return false;

	m_customCmds.insert(std::make_pair(aName, std::make_pair(aDir,aCmd)));

    return true;
}
// -----------------------------------------------------------------------------
bool Project::removeCustomCmd (const std::string& aName)
{
	auto found (m_customCmds.find(aName));
    if (found == m_customCmds.end()) return false;

    m_customCmds.erase(found);

    return true;
}
// -----------------------------------------------------------------------------
Project::CustomCmd Project::getCustomCmd (const std::string& aName) const
{
    auto found {m_customCmds.find(aName)};
    if (found != m_customCmds.end()) return std::make_pair(std::string{}, std::string{});

    return found->second;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
