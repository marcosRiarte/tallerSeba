#include <json/json.h>
#include <iostream>
#include <string>

int runJsonTest() {

	std::string example =
			"{\"array\":[\"item1\", \"item2\"], \"not an array\":\"asdf\"}";
	Json::Value value;
	Json::Reader reader;

	bool parsed = reader.parse(example, value, false);
	if (parsed)
		std::cout << "FUNCIONA JSON \n";
	else
		std::cout << "NO FUNCIONA JSON \n";

	return 0;
}
