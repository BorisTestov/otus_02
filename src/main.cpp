#include "IpFilter.h"

int main()
{
    try
    {
        IpFilter ipFilter;
        ipFilter.read_pool();
        ipFilter.reverse_sort();
        ipFilter.print_pool();
        ipFilter.filter(1);
        ipFilter.print_pool();
		ipFilter.filter(46,70);
        ipFilter.print_pool();
		ipFilter.filter_any(46);
        ipFilter.print_pool();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

