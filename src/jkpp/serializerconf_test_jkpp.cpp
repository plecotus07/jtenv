// +++ -------------------------------------------------------------------------
#include "serializerconf_jkpp.hpp"

#include <catch/catch.hpp>
// +++ -------------------------------------------------------------------------
SCENARIO ("Conf file serializer") {
	GIVEN ("Closed serializer") {
		jkpp::SerializerConf ser {};

        WHEN ("Close") {
            THEN ("Throw exception") {
            	REQUIRE_THROWS(ser.close());
            }
		}
        WHEN ("Serialize string") {
            THEN ("Throw exception") {
            	std::string v {};
            	REQUIRE_THROWS(ser.serializeString("value", v));
            }
		}
        WHEN ("Serialize CSV string") {
            THEN ("Throw exception") {
            	std::vector<std::string> v {};

            	REQUIRE_THROWS(ser.serializeCsvString("value", '|', v));
            }
		}
    }

    GIVEN ("Serializer open for write") {
    	jkpp::SerializerConf ser {};
        std::ostringstream ss {};
        ser.openForWrite(ss);
        WHEN ("Serialize single line string") {
        	std::string s {"value1"};
        	THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeString("name1", s));
                AND_THEN ("Valid string is in stream") {
                    REQUIRE(ss.str() == "name1=\"value1\"\n");
                }
			}
        }
        WHEN ("Serialize multi line string") {
        	std::string s {"value1\nvalue2\nvalue3"};
        	THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeString("name2", s));
                AND_THEN ("Valid string is in stream") {
                    REQUIRE(ss.str() == "name2=\"value1\nvalue2\nvalue3\"\n");
                }
			}
        }
    }
}
// +++ -------------------------------------------------------------------------
