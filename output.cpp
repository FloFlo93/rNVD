#include<iostream>
using namespace std;

class Output {
private:
    bool quiet = false;
public:
    void set_quiet(bool quiet);
    void print_header();
    void print_usage();
    void print_result(double fvs, double svf, double rNVD);
};

void Output::set_quiet(bool quiet) {
    this->quiet = quiet;
}

void Output::print_header() {
    if(this->quiet) return;
    else cout << "Calculating the rNVD index, author: Florian Piewald, 2018" << endl << endl;
}

void Output::print_usage() {
    cout << "Usage: [path to first_cluster_set.json] [path to second_cluster_set.json] [threads]" << endl << endl;
}

void Output::print_result(double fvs, double svf, double rNVD) {
    if(this->quiet) printf("%f,%f,%f\n", fvs, svf, rNVD);
    else {
        cout << "MH (first vs. second) = " + to_string(fvs) << endl;
        cout << "MH (second vs. first) = " + to_string(svf) << endl;
        cout << "rNVD = " + to_string(rNVD) << endl;
    }
}
