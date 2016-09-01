#include <boost/multiprecision/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <functional>
#include <thread>
#include <vector>
#include <string>

void task_function_impl(const boost::multiprecision::mpz_int& rsa_number, const boost::multiprecision::mpz_int& dist_upper_bound){
    using namespace boost::multiprecision;
    using namespace boost::random;
    thread_local random_device rd;
    thread_local mt19937 mt(rd());
    uniform_int_distribution<mpz_int> dist(mpz_int(3),dist_upper_bound);
    mpz_int factor;
    while(1){
        mpz_mul_2exp(factor.backend().data(),dist(mt).backend().data(),1);
        mpz_add_ui(factor.backend().data(),factor.backend().data(),1);
        if(mpz_divisible_p(rsa_number.backend().data(),factor.backend().data())){
            std::ofstream ofs("factor.rsa");
            std::cout << factor << std::endl;
            ofs<<factor;
            ofs.close();
            abort();
        }

    }
}


int main(int argc, char* argv[]){
    using namespace boost::multiprecision;
    using namespace boost::random;
    namespace po= boost::program_options;

    int thread_number=1;
    mpz_int rsa_number;


    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h"                                      , "produce help message"                   )
            ("npos,n", po::value<int>()->default_value(1)  , "number of thread(s) to run this program")
            ("rsa,r" , po::value<int>()->required()        , "the index of RSA number"                )
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

        thread_number=vm["npos"].as<int>();


    std::ifstream ifs("./data/"+std::to_string(vm["rsa"].as<int>())+".rsa");
    if(!ifs){
        std::cout<<"Can't find the corresponding RSA number!\n";
        ifs.close();
        abort();
    }
    ifs>>rsa_number;
    ifs.close();

    //auto task_function=std::bind(task_function_impl,rsa_number,sqrt(rsa_number)/2);
    mpz_int dist_upper_bound=sqrt(rsa_number)/2;
    std::vector<std::thread> task_group;
    for(int i=0;i<thread_number;i++)
        task_group.emplace_back(task_function_impl,rsa_number,dist_upper_bound);

    for(auto itr=task_group.begin();itr!=task_group.end();itr++)
        itr->join();

    return 0;
}