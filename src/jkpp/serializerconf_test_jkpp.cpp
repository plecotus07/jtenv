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
        	std::string value1 {};
        	std::string value2 {};
        	THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeString("name1", value1));
                REQUIRE_NOTHROW(ser.serializeString("name2", value2));
                AND_THEN ("Values are valid") {
                    REQUIRE(value1 == "value1");
                    REQUIRE(value2 == "value2");
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
		WHEN ("Serialize CSV string with one element") {
        	std::vector<std::string> sv {};
            ss << "name4=\"value1\"\n";
        	THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeCsvString("name4", "|", sv));
                AND_THEN ("Value is valid") {
                    REQUIRE(sv.size() == 1);
                    REQUIRE(sv[0] == "value1");
                }
			}
        }
        WHEN ("Serialize file with line breaks.") {
        	ss << "\n\nname1=\"value1\"\n\n\nname2=\"value2\"\n";
            std::string value1 {};
            std::string value2 {};
            THEN ("No exception throws") {
            	REQUIRE_NOTHROW(ser.serializeString("name1", value1));
            	REQUIRE_NOTHROW(ser.serializeString("name2", value2));
                AND_THEN ("Value is valid") {
                	REQUIRE(value1 == "value1");
                	REQUIRE(value2 == "value2");
				}
            }
        }
        WHEN ("Serialize string with invalid name") {
        	ss << "name1=\"value1\"\nname2=\"value2\"\nname3=\"value3\"";
            std::string value {};
            THEN ("Exception throws") {
            	REQUIRE_THROWS(ser.serializeString("name4", value));
            	REQUIRE_THROWS(ser.serializeString("name3", value));
            }
        }
		WHEN ("Serialize broken file: EOF in key") {
        	ss << "name1=\"value1\"\nna";
            std::string value {};
			ser.serializeString("name1", value);
            THEN ("Exception throws") {
            	REQUIRE_THROWS(ser.serializeString("name2", value));
            }
        }
		WHEN ("Serialize broken file: line break in key") {
        	ss << "nam\ne1=\"value1\"\n";
            std::string value {};
            THEN ("Exception throws") {
            	REQUIRE_THROWS(ser.serializeString("name1", value));
            }
        }
		WHEN ("Serialize broken file: EOF in value") {
        	ss << "name1=\"value1\"\nname2=\"val";
            std::string value {};
			ser.serializeString("name1", value);
            THEN ("Exception throws") {
            	REQUIRE_THROWS(ser.serializeString("name2", value));
            }
        }
		WHEN ("Serialize broken file: Missing quote") {
			ss << "name1=\"value1\"\nname2=\"value2\nname3=\"value3\"";
			std::string value {};
			ser.serializeString("name1", value);
			THEN ("Exception throws") {
				REQUIRE_NOTHROW(ser.serializeString("name2", value));
				REQUIRE(value == "value2\nname3=");
				REQUIRE_THROWS(ser.serializeString("name3", value));
			}
		}
    }
}
// +++ -------------------------------------------------------------------------
