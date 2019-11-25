# Kattis solutions

Solutions for Kattis problems written in C++

Uses Bazel build system to build a problem solution use the following command:
```bash
bazel build "problem_name:all"
```
Or you can run tests using the command:
```bash
bazel test "problem_name:all"
```
Where `problem_name` is the name of the folder.

There are two custom scripts to help with downloading problems and submitting solutions.
- **new_problem.py**
Usage: ./new_problem.py <problem_name>
This script will initialize a new bazel folder with an empty solution for the given problem. It will also download all
samples and create a template unit test to assert that the sample outputs are correct.

- **submit.sh**
Usage: ./submit.sh <problem_name>
This uses the Kattis provided submit.py script to upload a given solution to kattis. Simply given the folder it will
upload any cpp/h/hpp files (excluding the unit tests) to Kattis.