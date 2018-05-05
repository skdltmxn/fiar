#pragma once

#include <string>

class web_request
{
public:
	explicit web_request(const std::string& host, unsigned short port) : _host(host), _port(port)
	{}
	std::string get(const std::string& to, const std::string& param, const std::string& value);

private:
	std::string _host;
	unsigned short _port;
};
