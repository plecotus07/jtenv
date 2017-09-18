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
}
// +++ -------------------------------------------------------------------------
