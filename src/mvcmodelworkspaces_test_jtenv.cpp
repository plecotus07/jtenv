// +++ -------------------------------------------------------------------------
#include "mvcmodelworkspaces_jtenv.hpp"

#include <filesystem_jkpp.hpp>

#include <iostream>

#include <catch/catch.hpp>
// +++ -------------------------------------------------------------------------
SCENARIO ("Workspaces model parse address") {
	GIVEN ("Workspaces model") {
        jtenv::MvcModelWorkspaces model;
        model.addWorkspace("ws1", nullptr, fs::current_path()/"workspaces"/"ws1");
        model.addWorkspace("ws3", nullptr, fs::current_path()/"workspaces"/"ws3");

        WHEN ("Address is empty and path is outside workspace") {
			auto names = model.parseAddress("", fs::current_path());

            THEN ("Project and workspace names are empty") {
            	REQUIRE(names.first.empty());
                REQUIRE(names.second.empty());
            }
		}
        WHEN ("Address is empty and path is in false workspace") {
			auto names = model.parseAddress("", fs::current_path() / "ws2");

            THEN ("Project and workspace names are empty") {
            	REQUIRE(names.first.empty());
                REQUIRE(names.second.empty());
            }
        }
        WHEN ("Address is empty and path is in workspace") {
			auto names = model.parseAddress("", fs::current_path() / "workspaces" / "ws1");

        	THEN ("Workspace name is found, but project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second.empty());
            }
        }
        WHEN ("Address is empty and path is in workspace no project sub dir") {
			auto names = model.parseAddress("", fs::current_path() / "workspaces" / "ws1" / "dir1" / "dir2");

        	THEN ("Workspace name is found, but project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second.empty());
            }
        }
        WHEN ("Address is empty and path is in project") {
			auto names = model.parseAddress("", fs::current_path() / "workspaces" / "ws1" / "proj11");

            THEN ("Workspace and project are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is empty and path is in project sub dir") {
			auto names = model.parseAddress("", fs::current_path() / "workspaces" / "ws1" / "proj11" / "dir1" / "dir2");

            THEN ("Workspace and project are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is workspace and path is outside workspace") {
			auto names = model.parseAddress("ws1", fs::current_path());

            THEN ("Workspace name is found and project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "");
            }
        }
        WHEN ("Address is workspace and path is in project") {
			auto names = model.parseAddress("ws1", fs::current_path() / "workspaces" / "ws1" / "proj11");

            THEN ("Workspace name is found and project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "");
            }
        }
        WHEN ("Address is workspace and path is in project sub dir") {
			auto names = model.parseAddress("ws1", fs::current_path() / "workspaces" / "ws1" / "proj11" / "sub1" / "sub2");

            THEN ("Workspace name is found and project name is empty") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "");
            }
        }
        WHEN ("Address is project and path is outside workspace") {
			auto names = model.parseAddress(":proj11", fs::current_path());

            THEN ("Project and workspace names are empty") {
            	REQUIRE(names.first.empty());
                REQUIRE(names.second.empty());
            }
		}
        WHEN ("Address is project and path is in workspace") {
			auto names = model.parseAddress(":proj11", fs::current_path() / "workspaces" / "ws1");

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is project and path is in workspace sub dir") {
			auto names = model.parseAddress(":proj11", fs::current_path() / "workspaces" / "ws1" / "dir1" / "dir2");

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is workspace and project and path is outside workspace") {
			auto names = model.parseAddress("ws1:proj11", fs::current_path());

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj11");
            }
		}
        WHEN ("Address is not cloned workspace") {
			auto names = model.parseAddress("ws2", fs::current_path());

            THEN ("Workspace names are found") {
            	REQUIRE(names.first == "ws2");
                REQUIRE(names.second == "");
            }
		}
        WHEN ("Address is not cloned workspace and project") {
			auto names = model.parseAddress("ws2:proj21", fs::current_path());

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws2");
                REQUIRE(names.second == "proj21");
            }
		}
        WHEN ("Address is workspace and not existing project") {
			auto names = model.parseAddress("ws1:proj", fs::current_path());

            THEN ("Project and workspace names are found") {
            	REQUIRE(names.first == "ws1");
                REQUIRE(names.second == "proj");
            }
		}

    }
}
// +++ -------------------------------------------------------------------------
