#include <IpFilter.h>

// Check if string is valid ip byte
bool IpFilter::is_valid_byte(const std::string& s)
{
    bool is_valid = false;
    try {
        int byte_value = std::stoi(s);
        if (byte_value >= 0 && byte_value <= 255){
            is_valid = true;
        }
    }
    catch(...){}
    return is_valid;
}

IpFilter::IpFilter(){}

IpFilter::~IpFilter(){}

std::vector<std::string> IpFilter::split(const std::string &str, char d)
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

std::vector<int> IpFilter::ip_str_to_int (const std::vector<std::string> &str_vector){
    // Check that we have only 4 elements in input vector
    // and all of this elements are in range 0...255
    std::vector<int> int_vector;
    std::vector<bool> valid_bytes;
    valid_bytes.reserve(str_vector.size());
    std::transform(str_vector.begin(),str_vector.end(),valid_bytes.begin(),this->is_valid_byte);
    if (str_vector.size() != 4 || std::find(valid_bytes.begin(),valid_bytes.end(),0) != valid_bytes.end()) {
        std::cout << "Incorrect IP format: " << std::endl;
        print_ip<std::string>(str_vector);
    }
    else {
        std::for_each(str_vector.begin(),str_vector.end(),[&int_vector](const std::string &str_byte){
            int_vector.push_back(std::stoi(str_byte));
        });
    }    
    return int_vector;
}

void IpFilter::reverse_sort(){
    std::sort(this->ip_pool.begin(), this->ip_pool.end(), std::greater<>());
	this->filtered_ip = ip_vector(this->ip_pool);
}

void IpFilter::filter_any(const int expected_value){
	this->filtered_ip.clear();
    std::copy_if(this->ip_pool.begin(), this->ip_pool.end(), std::back_inserter(this->filtered_ip), [&expected_value](const auto ip){
		return std::any_of(ip.begin(), ip.end(), [&expected_value](const int &ip_byte)
		{
			return ip_byte == expected_value;
		});
	});
}

void IpFilter::read_pool(){
	for(std::string line; std::getline(std::cin, line);)
	{
		std::vector<std::string> v = split(line, '\t');
		auto int_vector = ip_str_to_int(split(v.at(0), '.'));
        if (int_vector.size() != 0){
            this->ip_pool.push_back(int_vector);
        }
	}
	this->filtered_ip = ip_vector(this->ip_pool);
}

void IpFilter::print_pool(){
    std::for_each(this->filtered_ip.begin(),this->filtered_ip.end(),this->print_ip<int>);
}

