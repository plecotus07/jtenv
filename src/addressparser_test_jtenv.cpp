// +++ -------------------------------------------------------------------------
#include "addressparser_jtenv.hpp"
#include "workspace_jtenv.hpp"
#include <gitsubproc_jkpp.hpp>

#include <catch/catch.hpp>
// +++ -------------------------------------------------------------------------
SCENARIO ("Address parser") {
	GIVEN ("Parser with given workspaces") {
        jkpp::GitSubProcBuilder git_builder {};
    	jtenv::Workspace::SPtrByStrMap workspaces {
        	{"ws1", std::make_shared<jtenv::Workspace>("ws1", nullptr, git_builder.create((fs::current_path()/"workspaces"/"ws1").string()))},
	        {"ws2", std::make_shared<jtenv::Workspace>("ws2", nullptr)},
	        {"ws3", std::make_shared<jtenv::Workspace>("ws3", nullptr, git_builder.create((fs::current_path()/"workspaces"/"ws3").string()))},
        };
        jtenv::AddressParser parser {workspaces};

        WHEN ("Address is empty and path is outside workspace") {
			auto names = parser("");

            THEN ("Project and workspace names are empty") {
            	REQUIRE(names.first.empty());
                REQUIRE(names.second.empty());
            }
		}
        WHEN ("Address is empty and path is in false workspace") {
			auto names = parser("", fs::current_path() / "ws2");

            THEN ("Project and workspace names are empty") {
            	REQUIRE(names.first.empty());
                REQUIRE(names.second.empty());
            }
        }
        WHEN ("Address is empty and path is in workspace") {
			auto names = parser("", fs::current_path() / "workspaces" / "ws1");

        	THEN ("Workspace name is found, but project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second.empty());
            }
        }
        WHEN ("Address is empty and path is in workspace no project sub dir") {
			auto names = parser("", fs::current_path() / "workspaces" / "ws1" / "dir1" / "dir2");

        	THEN ("Workspace name is found, but project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second.empty());
            }
        }
        WHEN ("Address is empty and path is in project") {
			auto names = parser("", fs::current_path() / "workspaces" / "ws1" / "proj11");

            THEN ("Workspace and project are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is empty and path is in project sub dir") {
			auto names = parser("", fs::current_path() / "workspaces" / "ws1" / "proj11" / "dir1" / "dir2");

            THEN ("Workspace and project are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is workspace and path is outside workspace") {
			auto names = parser("ws1");

            THEN ("Workspace name is found and project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "");
            }
        }
        WHEN ("Address is workspace and path is in project") {
			auto names = parser("ws1", fs::current_path() / "workspaces" / "ws1" / "proj11");

            THEN ("Workspace name is found and project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "");
            }
        }
        WHEN ("Address is workspace and path is in project sub dir") {
			auto names = parser("ws1", fs::current_path() / "workspaces" / "ws1" / "proj11" / "sub1" / "sub2");

            THEN ("Workspace name is found and project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "");
            }
        }
        WHEN ("Address is project and path is outside workspace") {
			auto names = parser(":proj11");

            THEN ("Project and workspace names are empty") {
            	REQUIRE(names.first.empty());
                REQUIRE(names.second.empty());
            }
		}
        WHEN ("Address is project and path is in workspace") {
			auto names = parser(":proj11", fs::current_path() / "workspaces" / "ws1");

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
		WHEN ("Address is not existing project and path is in workspace") {
			auto names = parser(":proj15", fs::current_path() / "workspaces" / "ws1");

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj15");
            }
		}
        WHEN ("Address is project and path is in workspace sub dir") {
			auto names = parser(":proj11", fs::current_path() / "workspaces" / "ws1" / "dir1" / "dir2");

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is workspace and project and path is outside workspace") {
			auto names = parser("ws1:proj11");

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is not cloned workspace") {
			auto names = parser("ws2");

            THEN ("Workspace names are found") {
            	REQUIRE(names.first == "ws2");
                REQUIRE(names.second == "");
            }
		}
        WHEN ("Address is not cloned workspace and project") {
			auto names = parser("ws2:proj21");

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws2");
                REQUIRE(names.second == "proj21");
            }
		}
        WHEN ("Address is workspace and not existing project") {
			auto names = parser("ws1:proj");

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj");
            }
		}

    }
}
// +++ -------------------------------------------------------------------------
