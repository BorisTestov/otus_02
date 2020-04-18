#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_vector = std::vector<std::vector<int>>;

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector<int> ip_str_to_int (const std::vector<std::string> &str_vector){
    std::vector<int> int_vector;
    std::for_each(str_vector.begin(),str_vector.end(),[&int_vector](const std::string &str_byte){
        int_vector.push_back(std::stoi(str_byte));
    });
    return int_vector;
}

void print_ip(std::vector<int> ip){
    for(auto ip_part = ip.begin(); ip_part != ip.end(); ++ip_part)
    {
        if (ip_part != ip.begin())
        {
            std::cout << ".";

        }
        std::cout << *ip_part;
    }
	std::cout << std::endl;
}

void reverse_sort(ip_vector &pool){
    std::sort(pool.begin(), pool.end(), std::greater<>());
}

template<typename... T>
ip_vector filter(const ip_vector &pool,T const & ... args){

	std::vector<int> byte_values = {args...};
    ip_vector filtered_ip;
    std::copy_if(pool.begin(),pool.end(),std::back_inserter(filtered_ip),[&byte_values](const auto ip){
        return std::equal(ip.begin(),ip.begin() + byte_values.size(), byte_values.begin());
    });
    return filtered_ip;
}

ip_vector filter_any(const ip_vector &pool, const int &expected_value){
	ip_vector filtered_ip;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(filtered_ip), [&expected_value](const auto ip){
		return std::any_of(ip.begin(), ip.end(), [&expected_value](const int &ip_byte)
		{
			return ip_byte == expected_value;
		});
	});
    return filtered_ip;
}

int main()
{
    try
    {
        ip_vector ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(ip_str_to_int(split(v.at(0), '.')));
        }
		reverse_sort(ip_pool);

        std::for_each(ip_pool.begin(),ip_pool.end(),print_ip);

        ip_vector filtered_ip = filter(ip_pool,1);
        std::for_each(filtered_ip.begin(),filtered_ip.end(),print_ip);
		filtered_ip.clear();

		filtered_ip = filter(ip_pool,46,70);
        std::for_each(filtered_ip.begin(),filtered_ip.end(),print_ip);
		filtered_ip.clear();

		filtered_ip = filter_any(ip_pool,46);
        std::for_each(filtered_ip.begin(),filtered_ip.end(),print_ip);
		filtered_ip.clear();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
