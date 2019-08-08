#!/usr/bin/python

import sys
import os
import shutil
import tempfile
import requests
from zipfile import ZipFile

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

def fetchSamples(name, tmp_file = None):
    url = 'https://open.kattis.com/problems/{0}/file/statement/samples.zip'.format(name)
    r = requests.get(url, stream=True)
    
    if tmp_file is None:
        tmp_file = tempfile.TemporaryFile()
    
    shutil.copyfileobj(r.raw, tmp_file)

    tmp_file.seek(0)

    return tmp_file

def copyTemplate(src, dst, replDict):

    with open(src, 'r') as f:
        content = f.read()
    
    for old,new in replDict.items():
        content = content.replace(old, new)

    with open(dst, 'w') as f:
        f.write(content)



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

    if not os.path.exists(sample_dir):
        os.makedirs(sample_dir)

    replDict = {
        "__name__": name,
        "__aname__": aname,
        "__Name__": name.capitalize()
    }
    
    copyTemplate('template/main.cpp', os.path.join(name, 'main.cpp'), replDict)
    copyTemplate('template/__name__.cpp', os.path.join(name, name + '.cpp'), replDict)
    copyTemplate('template/__name__.hpp', os.path.join(name, name + '.hpp'), replDict)
    copyTemplate('template/_BUILD', os.path.join(name, 'BUILD'), replDict)

    with fetchSamples(name) as sample_zip_file:
        with ZipFile(sample_zip_file) as zipObj:
            sample_names = [ os.path.splitext(sample_name)[0] for sample_name in zipObj.namelist() if sample_name.endswith('.in') ]
            zipObj.extractall(sample_dir)
        
    with open(os.path.join(name, 'test.cpp'), 'w') as f:
        f.write(testIncludeString.format(name = name))
        for sample_name in sample_names:
            s = testSampleBodyString.format(
                aname = aname,
                name = name,
                Name = name.capitalize(),
                sample = sample_name,
                Sample = sample_name.capitalize()
            )
            f.write(s)