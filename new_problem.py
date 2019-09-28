#!/usr/bin/python

import sys
import os
import shutil
import tempfile
import requests
from zipfile import ZipFile
import argparse

testIncludeString = '''#include <sstream>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "{name}.hpp"
'''

testSampleBodyString = '''
TEST(Test{Name}, {Sample}Sample) {{

    std::stringstream ss;
    {{
        std::ifstream in("{name}/samples/{sample}.in");
        ASSERT_FALSE(in.fail());

        {aname}::solution(in, ss);
    }}

    std::ifstream ans("{name}/samples/{sample}.ans");
    ASSERT_FALSE(ans.fail());

    int lineCount = 0;
    std::string got, want;

    for (;;) {{
        std::getline(ss, got);
        std::getline(ans, want);
        if(ss.fail() && ans.fail()) {{
            break;
        }}

        ++lineCount;
        ASSERT_EQ(got, want) << "line = " << lineCount;
    }}
}}
'''


def usage():
    print('Usage: {0} <problem_name>'.format(sys.argv[0]))


def fetch_samples(name, tmp_file=None):
    url = 'https://open.kattis.com/problems/{0}/file/statement/samples.zip'.format(name)
    r = requests.get(url, stream=True)
    r.raise_for_status()

    if tmp_file is None:
        tmp_file = tempfile.TemporaryFile()

    shutil.copyfileobj(r.raw, tmp_file)

    tmp_file.seek(0)

    return tmp_file


def copy_template(src, dst, replDict):
    with open(src, 'r') as f:
        content = f.read()

    for old, new in replDict.items():
        content = content.replace(old, new)

    with open(dst, 'w') as f:
        f.write(content)


def write_tests(name, aname, sample_names):
    with open(os.path.join(name, 'test.cpp'), 'w') as f:
        f.write(testIncludeString.format(name=name))
        for sample_name in sample_names:
            s = testSampleBodyString.format(
                aname=aname,
                name=name,
                Name=name.capitalize(),
                sample=sample_name,
                Sample=sample_name.capitalize()
            )
            f.write(s)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()
        exit(1)

    name = sys.argv[1]
    if '0' <= name[0] <= '9':
        aname = '_' + name
    else:
        aname = name

    sample_dir = os.path.join(name, 'samples')

    try:
        with fetch_samples(name) as sample_zip_file:
            if not os.path.exists(sample_dir):
                os.makedirs(sample_dir)
            with ZipFile(sample_zip_file) as zipObj:
                zipObj.extractall(sample_dir)
                sample_names = [os.path.splitext(sample_name)[0] for sample_name in os.listdir(sample_dir) if
                                sample_name.endswith('.in')]
    except requests.exceptions.HTTPError as e:
        print('{name} not found.'.format(name=name))
        exit(1)

    replDict = {
        "__name__": name,
        "__aname__": aname,
        "__Name__": name.capitalize()
    }

    copy_template('template/main.cpp', os.path.join(name, 'main.cpp'), replDict)
    if not os.path.exists(os.path.join(name, name + '.cpp')):
        copy_template('template/__name__.cpp', os.path.join(name, name + '.cpp'), replDict)
        copy_template('template/__name__.hpp', os.path.join(name, name + '.hpp'), replDict)
    copy_template('template/_BUILD', os.path.join(name, 'BUILD'), replDict)

    write_tests(aname, name, sample_names)
