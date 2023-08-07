#include "dogapi_connector.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	// Initialize connector object
	DogApiConnector connector;

	// Call the getDogFact method to get a single random dog fact from the API
	string dogFact = connector.getDogFact();

	// Print the dog fact to standard output
	cout << dogFact << "\n";

	return 0;
}
