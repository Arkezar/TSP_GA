#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <catch.hpp>

int main(int argc, char *argv[]){	
	std::srand(std::time(0));
	int result = Catch::Session().run( argc, argv );
	return 0;
}
