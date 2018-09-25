#!/usr/bin/env python3
import inspect
import numpy as np
from subprocess import Popen, PIPE
from test_results import *

def get_first_file(var_name):
    return var_name.split("_")[0] + ".json"

def get_second_file(var_name):
    return var_name.split("_")[2] + ".json"

def compare(res_arr, test_name):
    res_arr = np.asarray(res_arr)
    true_res_arr = np.asarray(getattr(TestCases, test_name))
    test = np.allclose(res_arr, true_res_arr, atol=tolerance)
    return np.all(test)


def main():
    variables = [i for i in dir(TestCases) if not inspect.ismethod(i)]
    variables = [i for i in variables if not i[:1] == "_"]

    for i in variables:
        first_file = get_first_file(i)
        second_file = get_second_file(i)
        result = Popen(["../rNVD", first_file, second_file, "1", "q"], stdout=PIPE, encoding='utf8')
        res_str = result.communicate()[0]
        res_arr = res_str.split(",")
        res_arr = [float(i) for i in res_arr]
        test_passed = compare(res_arr, i)
        if(not test_passed):
            print(i + " failed")
            print(res_str)

main()
