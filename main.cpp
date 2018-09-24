#include "rNVD.cpp"
#include "json_parser.cpp"
#include<string>
#include <time.h>
using namespace std;

int main(int argc, char* argv[]) {

    cout << "Calculating the rNVD index, author: Florian Piewald, 2018" << endl << endl;
    if(argc < 3) {
        cout << "Usage: [path to first_cluster_set.json] [path to second_cluster_set.json] [threads]" << endl << endl;
    }

    string firstFile = argv[1];
    string secondFile = argv[2];
    int threads = stoi(argv[3]);


    vector<vector<string>> firstClusterSet = fromFile(firstFile);
    vector<vector<string>> secondClusterSet = fromFile(secondFile);



    time_t start = time(0);
    tuple<double, double, double, long long int, long long int> rNVD_all = get_rNVD(firstClusterSet, secondClusterSet, threads);

    if(get<3>(rNVD_all) != get<4>(rNVD_all)) cout << "WARNING, different n: " + to_string(get<3>(rNVD_all)) + " "  to_string(get<4>(rNVD_all)) << endl;
    else cout << "n= " + to_string(get<3>(rNVD_all) << endl;

    cout << "first vs. second = " + to_string(get<0>(rNVD_all)) << endl;
    cout << "second vs. first = " + to_string(get<1>(rNVD_all)) << endl;
    cout << "rNVD = " + to_string(get<2>(rNVD_all)) << endl;
    
    double seconds_since_start = difftime( time(0), start);
    cout << endl << endl << endl;
    cout << "calculated in " + to_string(seconds_since_start*1.0/60) + " (minutes)" << endl;
}
