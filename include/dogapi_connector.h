#ifndef __DOGAPI_CONNECTOR_H__
#define __DOGAPI_CONNECTOR_H__

#include <string>

#include "httplib.h"

using namespace std;

/*
 * Dog API Connector Class
 *
 * The Class maintains an http client connection to the Dog API endpoint
 * and provides methods for calling the API endpoints and parsing the responses
 *
 * For now we have the one and only method provided, getDogFact, which retrieves
 * a single dog fact from the API
 */
class DogApiConnector
{
	public:
		DogApiConnector();
		~DogApiConnector();

		/* Return the single random dog fact in a string, or an error string in case
		 * of failure */
		string getDogFact();

	private:
		/* The client connection is stored as a pointer because there's no
		 * default constructor and I wanted to avoid exposing the endpoint URL
		 * in the header file
		 * This is merely an arbitrary design choice and it forces the definitions
		 * of a constructor and destructor for this class, an alternative would have
		 * been to initialize a private member of type httplib::Client (not a pointer)
		 * and pass the argument:
		 *    httplib::Client client(URL)
		 */
		httplib::Client *client;
};

#endif // __DOGAPI_CONNECTOR_H__
