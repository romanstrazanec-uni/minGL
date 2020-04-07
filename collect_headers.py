import os
import re
from typing import Set, List

sep = '/'


def mkdir(path: List[str]):
    [os.mkdir(np) for np in (sep.join(path[:i]) for i in range(1, len(path))) if not os.path.exists(np)]


def collect_includes(file: str) -> Set[str]:
    with open(file) as f:
        return set(m.group(1) for m in (re.match(r'#include "(.*?)"', line) for line in f.readlines()) if m)


def collect_headers(file: str) -> Set[str]:
    result = {file}
    file_path = file.split(sep)
    for include in collect_includes(file):
        include_path = include.split(sep)
        path_without_back = [p for p in include_path if p != '..']
        step_back = len(path_without_back) - len(include_path) - 1
        result.update(collect_headers(sep.join(file_path[:step_back] + path_without_back)))
    return result


if __name__ == '__main__':
    for header in reversed(sorted(collect_headers(f'lib{sep}mingl'))):
        dst = f'includes{sep}{header}'
        mkdir(dst.split(sep))
        os.system(f'cp {header} {dst}')
