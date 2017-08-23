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
    m_defaultBranch {"master"}
{

}
// -----------------------------------------------------------------------------
bool Project::init (const std::string& aFullName, const std::string& aRepoUrl, jkpp::GitBuilder& aGitBuilder)
{
	m_fullName = aFullName;
    m_remoteGit = aGitBuilder.create();
    m_remoteGit->set(aRepoUrl);

	try {
		fs::create_directories(m_path);
	} catch (...) {
		return false;
	}

    return save();
}
// -----------------------------------------------------------------------------
bool Project::load (jkpp::GitBuilder& aGitBuilder)
{
    if (!fs::exists(m_path / "project.conf")) return false;

    std::ifstream file {(m_path / "project.conf").string(), std::fstream::in};
    if (!file) return false;

    std::string line {};
std::cerr << "+++: " << m_path / (m_name + "_repo") << '\n';

    while (std::getline(file, line)) {
		auto pos {line.find_first_of('=')};
        if (pos == std::string::npos) return false;

        std::string key {line.substr(0, pos)};
        std::string value {line.substr(pos + 1)};

        if (key == "repo_url") {
        	m_remoteGit = aGitBuilder.create();
            m_remoteGit->set(value);
        } else if (key == "full_name") m_fullName = value;
        else if (key == "default_branch") m_defaultBranch = value;
        else return false;
    }

	if (fs::exists(m_path / (m_name + "_repo"))) {
		m_git = aGitBuilder.create();
	    m_git->set((m_path / (m_name + "_repo")).string());
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
    file << "repo_url=" << m_remoteGit->getPath() << '\n';
    file << "default_branch=" << m_defaultBranch << '\n';

    file.close();

    return true;
}
// -----------------------------------------------------------------------------
bool Project::clone (const std::string& aUserName, const std::string& aUserEmail)
{
	if (!m_remoteGit) return false;

	jkpp::Git::UPtr git {m_remoteGit->clone((m_path / (m_name + "_repo")).string(), false)};
    if (!git) return false;
    m_git = std::move(git);

    m_git->command("checkout " + m_defaultBranch);

	return true;
}
// -----------------------------------------------------------------------------
bool Project::git (const std::string& aCommand)
{
	if (!m_git) return false;

    return m_git->command(aCommand);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
