#include "dogapi_connector.h"

using namespace std;

const char DOG_API_URL[] = "https://dog-api.kinduff.com";
const char DOG_FACTS_EP[] = "/api/facts?number=1";

/*
 * Remove backslashes from escaped double quotes
 */
static void unescapeQuotes(string &result)
{
	string::iterator it;
	for (it = result.begin(); it != result.end(); it++)
	{
		if ( *it == '"' && it != result.begin() && *(it-1) == '\\' )
		{
			// if such a sequence is found, remove the backslash (previous character)
			// and set the iterator back just in case we have double-escaped seqeuences
			result.erase(it-1);
			it--;
		}
	}
}

/*
 * Parse the response
 *
 * Ideally here we'd use a JSON parser but I didn't want to introduce a dependency
 * for what's quite literally 20 lines of code in a POC
 *
 * For this parser to work properly we assume there is only one fact returned from
 * the API
 *
 * This function returns a status code, any status other than zero is an error:
 * 1: the "success": true string was not found in response
 * 2: the "facts" array was not found in response
 * 3: the "facts" array did not terminate properly
 */
static int parseDogFact(string &result, const string jsonData)
{
	(void)result;
	size_t pos, l, r;

	pos = jsonData.find("\"success\":true");
	if (pos == string::npos)
		return 1;

	pos = jsonData.find("\"facts\":[");
	if (pos == string::npos)
		return 2;

	l = pos + 10;
	pos = jsonData.find("\"]", l);
	if (pos == string::npos)
		return 3;
	r = pos;

	result.assign(jsonData.substr(l, r-l));
	unescapeQuotes(result);

	return 0;
}

DogApiConnector::DogApiConnector()
{
	// Initialize the client object with the API url
	this->client = new httplib::Client(DOG_API_URL);
}

DogApiConnector::~DogApiConnector()
{
	// Free the client object
	delete this->client;
}

/* Return the single random dog fact in a string, or an error string in case
 * of failure */
string DogApiConnector::getDogFact()
{
	string ret;

	// GET request
	auto res = this->client->Get(DOG_FACTS_EP);

	// Check the status code
	// Ideally here we'd use some way of handling errors, such as exceptions or
	// status codes
	// However since all output ends up on the console anyway this should be enough
	// for now
	if (res->status != 200)
	{
		ret.assign("Could not get response from API server");
		return ret;
	}

	// Parse the response and report any parse errors
	if (parseDogFact(ret, res->body))
	{
		ret.assign("Invalid response: ");
		ret.append(res->body);
		return ret;
	}

	return ret;
}
