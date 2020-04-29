import os
import re
from typing import List

sep = '/'


def mkdir(path: List[str]):
    [os.mkdir(np) for np in (sep.join(path[:i]) for i in range(1, len(path))) if not os.path.exists(np)]


class HeaderFile:
    _pool = []

    def __init__(self, file: str):
        try:
            hf = next(h for h in HeaderFile._pool if h.file == file)
            self.file = hf.file
            self.includes = hf.includes
            self.__collected = hf.collected
            self.dependencies = hf.dependencies
        except StopIteration:
            self.file = file
            self.includes = set()
            self.__collected = False
            self.dependencies = []
            HeaderFile._pool.append(self)

    @property
    def collected(self) -> bool:
        return self.__collected

    def collect_includes(self):
        """Collects files from: #include "../relative/path/to/file\"."""
        if not self.collected:
            with open(self.file) as f:
                self.includes = set(m.group(1) for m in (re.match(r'#include "(.*?)"', i) for i in f.readlines()) if m)
                self.__collected = True

    def collect_dependencies(self):
        """Collects all includes recursively."""
        if not self.collected:
            self.dependencies.append(self)
            file_path = self.file.split(sep)
            self.collect_includes()
            for include in self.includes:
                include_path = include.split(sep)
                path_without_back = [p for p in include_path if p != '..']
                step_back = len(path_without_back) - len(include_path) - 1
                hf = HeaderFile(sep.join(file_path[:step_back] + path_without_back))
                hf.collect_dependencies()
                self.dependencies.extend(hf.dependencies)

    def __eq__(self, other):
        return self.file.__eq__(other.file)

    def __lt__(self, other):
        return self.file.__lt__(other.file)


if __name__ == '__main__':
    mingl = HeaderFile(f'src{sep}mingl')
    mingl.collect_dependencies()
    for dependency in reversed(sorted(map(lambda d: d.file, mingl.dependencies))):
        dst = f'include{sep}minGL{dependency.replace("src", "")}'
        mkdir(dst.split(sep))
        os.system(f'cp {dependency} {dst}')
