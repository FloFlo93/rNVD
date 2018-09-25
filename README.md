<b>Author: Florian Piewald </b>
<b>Affiliation:<b> Affiliation: [Division of Computational Systems Biology (CUBE), University of Vienna](http://cube.univie.ac.at/) </b>

rNVD (reverse normalized Van Dongen index) is a program that allows to calculate the similarity of two clusterings.

# Requirements
The program has been tested on Linux (Fedora 27 and CentOS 7.5 using the GCC compiler). The usage of the program may not be per se limited to Linux, however it has not been explicitly tested on other systems.

# Installation

1. Clone the github repository
```git clone https://github.com/FloFlo93/rNVD```

2. Change into the directory
```cd rNVD/ ```

3. Run the installation script
```./install```

# Usage

```./rNVD first_file.json second_file.json threads [-q]```

In this example, first_clustering.json will be compared to second_clusterung.json using 4 threads. The result will be printed to stdout in a user friendly way:

```./rNVD first_clustering.json second_clustering.json 4```

In case an output suitable to be read by other programs, -q can be added (note that all arguments are positional and that you can only add -q as last parameter). In this case, the raw results (without any further explanation) are written to stdout seperated by comma.

```./rNVD first_clustering.json second_clustering.json 4 -q```

## The required format of the clusterings
Each clustering is represented as json file. The format is consistent with the format to represent gene clusters, which is used in the [PICA-to-go](https://github.com/FloFlo93/PICA-to-go) project. While the key is the name of the cluster (is not further processed, can be left empty), the value contains all items seperated by whitespace. It is required that each item has an unique name.

e.g.
'''json
{"1":"A B C D E",
"2":"F G H I J",
"3":"K L M N O"}
'''

In this case, we have a clustering containing three clusters. Each item of a cluster is represented by an unique single character.

## Output
The program outputs reverse normalized Van Dongen (rNVD) index as well as the Meila-Heckerman (MH) index, which is closely related to the Van Dongen index, but is not symmetric. In other words first_clustering.json vs. second_clustering.json will return a different result than second_clustering.json vs. first_clustering.json. The program will calculate both first. vs. second and second vs. first automatically.
In case the -q option is used, the results will be in the following order: MH first vs. second, MH second vs. first, rNVD.

# Background

## Origin of the project
This project originates from the evaluation of clusterings in regard to the [PICA-to-go](https://github.com/FloFlo93/PICA-to-go) project. Due to the high number of items in these gene clusterings, classical pair matching algorithm (such as the Rand index) may be computationally unfeasable. Therefore, a modified version of the Van Dongen measure was considered for this problem.

## Algorithmic background
The Van Dongen measure is a set matching algorithm to compare clusterings. Set matching means that for each cluster of the first clustering the cluster with the largest intersection in the second clustering is searched. This is done for each cluster of the first clustering and the intersection is summed up. For the Meila-Heckerman index this value is now divided by the number of items (n). In case of the Van Dongen measure, the number of maximal intersections is also summed up using the clusters of the 2nd clustering. Originally, the overall sum is substracted from 2n to gain the Van Dongen measure ([Wagner 2007](https://publikationen.bibliothek.kit.edu/1000011477)). As this value may not be very meaningful, a normalization is described in literature by dividing this value with 2n ([Rezaei et al., 2016](https://doi.org/10.1109/TKDE.2016.2551240)). This would mean that the a value of zero corresponds to identical clusterings, which is counterintuitive. Therefore, I introduced a reversed normalization of this index ranging from zero to one (with one meaning that the clusters are identical).

<img src="https://www.codecogs.com/latex/eqneditor.php?latex=rNVD = \cfrac{\sum_{i=1}^{K} max_{j=1}^{K'} Intersection_{ij} + \sum_{j=1}^{K'} max_{i=1}^{K} Intersection_{ij}}{2n}" />

<img src="https://www.codecogs.com/latex/eqneditor.php?latex=MH = \cfrac{\sum_{i=1}^{K} max_{j=1}^{K'} Intersection_{ij}}{n}" />


# Tests

A small number of test cases (5) are available in the sub directory tests. These tests have been manually evaluated and the result of the manual evaluation will be compared to the output of the rNVD software. test.py will automatically start with the evaluation. In case a test failed, this will be written to stdout.
