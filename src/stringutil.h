#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <sstream>

/* casts */

/**
 * string to float
 */
static float f_cast(const std::string& s) {
	std::istringstream stream (s);
    float t;
    stream >> t;
    return t;
}

static int i_cast(const std::string& s) {
	std::istringstream stream (s);
    int t;
    stream >> t;
    return t;
}

/**
 * float to string.
 */
static std::string s_cast(const float& t)
{
     std::ostringstream stream;
     stream << t;
     return stream.str();
}

/**
 * integer to string.
 */
static std::string s_cast(const int& t)
{
     std::ostringstream stream;
     stream << t;
     return stream.str();
}

/* safe casts. will throw if cast is not valid. */

static float f_scast(const std::string& s) {
	float tmp = f_cast(s);
	if(s != s_cast(tmp)) {
		throw int();
	}
	return tmp;
}

static int i_scast(const std::string& s) {
	int tmp = i_cast(s);
	if(s != s_cast(tmp)) {
		throw int();
	}
	return tmp;
}

#endif