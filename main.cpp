#include "rNVD.cpp"
#include "json_parser.cpp"
#include<string>
#include <time.h>
#include <cstring>
#include "output.cpp"
using namespace std;

int main(int argc, char* argv[]) {

    Output output = Output();

    if(argc < 3) {
        output.print_usage();
    }

    string firstFile = argv[1];
    string secondFile = argv[2];
    int threads = stoi(argv[3]);

    if(argc == 5 && strcmp(argv[4], "q") == 0) output.set_quiet(true);

    output.print_header();

    vector<vector<string>> firstClusterSet = fromFile(firstFile);
    vector<vector<string>> secondClusterSet = fromFile(secondFile);

    tuple<double, double, double, long long int, long long int> rNVD_all = get_rNVD(firstClusterSet, secondClusterSet, threads);

    output.print_result(get<0>(rNVD_all), get<1>(rNVD_all), get<2>(rNVD_all));

}
