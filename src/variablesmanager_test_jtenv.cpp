// +++ -------------------------------------------------------------------------
#include "variablesmanager_jtenv.hpp"
#include <catch/catch.hpp>
#include <iostream>
// +++ -------------------------------------------------------------------------
SCENARIO ("Variables manager") {
	GIVEN ("Empty variables manager") {
    	jtenv::VariablesManager vm {};

        THEN ("There is no variables in manager") {
           	REQUIRE(vm.getVariables().empty());
        }
        WHEN ("Add first variable") {
        	THEN ("There is no exception") {
            	auto s = vm.getVariables().size();
				REQUIRE_NOTHROW(vm.addVariable("var1", "value1"));
                THEN ("There is one variable more in manager") {
	            	REQUIRE(vm.getVariables().size() == s + 1);
                }
                AND_THEN ("Variable is added variable in manager") {
                    REQUIRE (vm.getVariable("var1") == "value1");
                }
			}
		}
    }
    GIVEN ("Variables manager with some variables") {
    	jtenv::VariablesManager vm {};
        vm.addVariable("var1", "value1");
        vm.addVariable("var2", "value2");
        vm.addVariable("var3", "value3");
		WHEN ("Add variable that already exists") {
        	THEN ("There is exception") {
				REQUIRE_THROWS(vm.addVariable("var1", "value1"));
            }
        }
        WHEN ("Get variable than not exists") {
            THEN ("Throw exception") {
                REQUIRE_THROWS(vm.getVariable("var4"));
            }
        }
    }
    GIVEN ("Variables manager with two submanagers") {
    	jtenv::VariablesManager vm {};
        vm.addVariable("var1", "value11");
        vm.addVariable("var3", "value3");
		auto svm1 {std::make_shared<jtenv::VariablesManager>()};
        svm1->addVariable("var1", "value12");
        svm1->addVariable("var4", "value42");
        svm1->addVariable("var5", "value5");
		auto svm2 {std::make_shared<jtenv::VariablesManager>()};
        svm2->addVariable("var1", "value13");
        svm2->addVariable("var5", "value53");
        svm2->addVariable("var6", "value6");

		vm.addSubManager(svm1);
        vm.addSubManager(svm2);

        WHEN("Get non-existent variable") {
        	THEN ("Throw exception") {
            	REQUIRE_THROWS(vm.getVariable("var7"));
            }
        }
        WHEN("Get variable that is in first manager") {
        	std::string var {vm.getVariable("var3")};
            THEN("We get it") {
            	REQUIRE(var == "value3");
            }
        }
        WHEN("Get variable that is in second manager") {
        	std::string var {vm.getVariable("var5")};
            THEN("We get it") {
            	REQUIRE(var == "value5");
            }
        }
        WHEN("Get variable that is in third manager") {
        	std::string var {vm.getVariable("var6")};
            THEN("We get it") {
            	REQUIRE(var == "value6");
            }
        }
        WHEN("Get variable that is in all managers") {
        	std::string var {vm.getVariable("var1")};
            THEN("We get it from first manager") {
            	REQUIRE(var == "value11");
            }
        }
    }
}
// +++ -------------------------------------------------------------------------
