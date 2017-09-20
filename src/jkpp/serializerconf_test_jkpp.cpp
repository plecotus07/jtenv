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

            	REQUIRE_THROWS(ser.serializeCsvString("value", "|", v));
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
        WHEN ("Serialize CSV string") {
        	std::vector<std::string> sv {"value1", "value2", "value3"};
        	THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeCsvString("name3", "|", sv));
                AND_THEN ("Valid string is in stream") {
                    REQUIRE(ss.str() == "name3=\"value1|value2|value3\"\n");
                }
			}
        }
	}

    GIVEN ("Serializer open for read") {
    	jkpp::SerializerConf ser {};
        std::stringstream ss {};
        ser.openForRead(ss);
        WHEN ("Serialize single line string") {
        	ss << "name1=\"value1\"\nname2=\"value2\"\n";
        	std::string s {};
        	THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeString("name1", s));
                AND_THEN ("Value is valid") {
                    REQUIRE(s == "value1");
                    AND_WHEN("Serialize next value") {
						s.clear();
                        THEN ("No exception throws") {
                            REQUIRE_NOTHROW(ser.serializeString("name2", s));
                            AND_THEN ("Value is valid") {
                                REQUIRE(s == "value2");
                            }
                        }
                    }
                }
			}
        }
        WHEN ("Serialize multi line string") {
        	ss << "name3=\"value1\nvalue2\nvalue3\"\n";
        	std::string s {};
        	THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeString("name3", s));
                AND_THEN ("Value is valid") {
                    REQUIRE(s == "value1\nvalue2\nvalue3");
                }
			}
        }
        WHEN ("Serialize CSV string") {
        	std::vector<std::string> sv {};
            ss << "name4=\"value1|value2|value3\"\n";
        	THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeCsvString("name4", "|", sv));
                AND_THEN ("Value is valid") {
                    REQUIRE(sv.size() == 3);
                    REQUIRE(sv[0] == "value1");
                    REQUIRE(sv[1] == "value2");
                    REQUIRE(sv[2] == "value3");
                }
			}
        }
    }
}
// +++ -------------------------------------------------------------------------
