#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_vector = std::vector<std::vector<int>>;

class IpFilter{

public:
    IpFilter();
    ~IpFilter();


    void filter_any(const int expected_value);
    void reverse_sort();
    void print_pool();
    void read_pool();

	template<typename... T>
	void filter(T const ... args){
		this->filtered_ip.clear();
		std::vector<int> byte_values = {args...};
		std::copy_if(this->ip_pool.begin(),this->ip_pool.end(),std::back_inserter(this->filtered_ip),[&byte_values](const auto ip){
			return std::equal(ip.begin(),ip.begin() + byte_values.size(), byte_values.begin());
		});
	}

	template<typename T>
	static void print_ip(std::vector<T> ip){
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
    std::vector<std::string> split(const std::string &str, char d);
    std::vector<int> ip_str_to_int (const std::vector<std::string> &str_vector);
	static bool is_valid_byte(const std::string& s);
private:
    ip_vector ip_pool;
    ip_vector filtered_ip;
    
};

