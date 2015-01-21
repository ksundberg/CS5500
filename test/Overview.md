##Unit Tests

We're currently using [Catch](https://github.com/philsquared/Catch) as a testing suite. To add a test, be sure to have

	#include <catch.hpp>
in your .cpp file.

##Run Tests on Linux/Unix
After running cmake on the project directory, run

	make test_run && make test
