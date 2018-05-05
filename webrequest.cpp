#include "webrequest.h"
#include <Winsock2.h>
#include <sstream>
#include <vector>

#pragma warning(disable: 4996)

std::string web_request::get(const std::string& to, const std::string& param, const std::string& value)
{
	std::stringstream req;

	req << "GET " << (to[0] == '/' ? to : "/" + to) << "?" << param << "=" << value << " HTTP/1.1\r\n";
	req << "HOST: " << _host << "\r\n";
	//req << "Connection: keep-alive\r\n";
	req << "\r\n";

	auto s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr = { 0, };
	auto host = gethostbyname(_host.c_str());

	addr.sin_family = AF_INET;
	addr.sin_addr = *(IN_ADDR *)host->h_addr_list[0];
	addr.sin_port = htons(_port);

	if (connect(s, (SOCKADDR *)&addr, sizeof(addr)) < 0)
	{
		throw std::exception("Cannot connect to host");
	}

	auto raw_req = req.str();
	send(s, raw_req.c_str(), (int)raw_req.size(), 0);

	std::vector<char> res;
	char buf[1024];
	while (1)
	{
		int recved = recv(s, buf, 1024, 0);
		if (recved <= 0)
			break;

		res.insert(res.end(), std::begin(buf), std::begin(buf) + recved);
	}

	closesocket(s);
	std::string res_str(res.data());
	
	return std::move(res_str.substr(res_str.find("\r\n\r\n") + 4));
}