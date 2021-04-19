from setuptools import Distribution
import setuptools.command.build_ext as _build_ext
from distutils.core import setup, Extension
import sysconfig
from pathlib import Path
import sys
import subprocess

"""
class build_ext(_build_ext.build_ext):
    def run(self):
            command = ["bash", "build.sh", "-p", sys.executable]
            subprocess.check_call(command)

class BinaryDistribution(Distribution):
    def has_ext_modules(self):
        return True

def main():
    # Use the setup function we imported and set up the modules.
    # You may find this reference helpful: https://docs.python.org/3.6/extending/building.html
    CFLAGS = ['-march=native', '-O3', '-pthread', '-Wall']
    
    #'AnytimeFrenetPlanner.cpp'
    module = Extension('fot_planner',
                    sources = ['planner_package.cpp'],
                    extra_compile_args = CFLAGS)

    setup(name="fot_planner",
        version="1.0.0",
        description="FOT Planner",
        author="ERDOS Project",
        cmdclass={"build_ext": build_ext},
        distclass= BinaryDistribution,
        package_data={'': ['libFrenetOptimalTrajectory.so']},
        ext_modules=[module])

if __name__ == "__main__":
    main()
"""


module = Extension('my_package', sources = ['package.cpp'], language="c++")

setup(name = 'my_package', version = '1.0',
    description = 'Python Package with superfastcode C++ extension',
    ext_modules = [module]
    )
