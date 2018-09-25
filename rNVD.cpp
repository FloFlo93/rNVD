#include<iostream>
#include<unordered_set>
#include<omp.h>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

tuple<double, double, double, long long int, long long int> get_rNVD(vector<vector<string>>& firstClusterSet, vector<vector<string>>& secondClusterSet, int threads);

static long long int countAllItems(vector<vector<string>>& clusterSet);
static long long int matchAllVsAll(vector<vector<string>>& firstClusterSet, vector<vector<string>>& secondClusterSet);
static long long int matching(vector<string>& cluster, vector<vector<string>>& clusterSet);
static long long int getIntersection(vector<string>& firstCluster, vector<string>& secondCluster);


//first: firstCluster vs. secondCluster; second: secondCluster vs. firstCluster; third: rNVD, four: nFirst, five nSecond
tuple<double, double, double, long long int, long long int> get_rNVD(vector<vector<string>>& firstClusterSet, vector<vector<string>>& secondClusterSet, int threads) {
    omp_set_num_threads(threads);
    long long int nFirst = countAllItems(firstClusterSet);
    long long int nSecond = countAllItems(secondClusterSet);
    long long int firstIntersectionSum =  matchAllVsAll(firstClusterSet, secondClusterSet);
    long long int secondIntersectionSum =  matchAllVsAll(secondClusterSet, firstClusterSet);
    double firstVsSecond = firstIntersectionSum*1.0/nFirst;
    double secondVsFirst = secondIntersectionSum*1.0/nSecond;
    double rNVD = (firstIntersectionSum + secondIntersectionSum)*1.0/(nFirst + nSecond);
    return make_tuple(firstVsSecond, secondVsFirst, rNVD, nFirst, nSecond);
}

static long long int countAllItems(vector<vector<string>>& clusterSet) {
    int count = 0;
    for(vector<string> cluster : clusterSet) {
        count += cluster.size();
    }
    return count;
}

static long long int matchAllVsAll(vector<vector<string>>& firstClusterSet, vector<vector<string>>& secondClusterSet) {
    long long int intersectionSum = 0;

    #pragma omp parallel for reduction(+:intersectionSum)
    for(unsigned int i=0; i<firstClusterSet.size(); i++) {
        vector<string> itemsFirstClusterSet = firstClusterSet[i];
        intersectionSum += matching(itemsFirstClusterSet, secondClusterSet);
    }
    return intersectionSum;
}

//matches the cluster (first argument) against a clusterSet (second argument) and returns the maximal intersection
static long long int matching(vector<string>& cluster, vector<vector<string>>& clusterSet) {
    long long int intersection = 0;
    #pragma omp simd
    for(int i=0; i<clusterSet.size(); i++) {
        long long int intersectionTmp;
        intersectionTmp = getIntersection(cluster, clusterSet[i]);
        if(intersectionTmp > intersection) intersection = intersectionTmp;
    }
    return intersection;
}

static long long int getIntersection(vector<string>& firstCluster, vector<string>& secondCluster) {
    vector<string> intersection;
    set_intersection(firstCluster.begin(), firstCluster.end(), secondCluster.begin(), secondCluster.end(), back_inserter(intersection));
    return intersection.size();
}
