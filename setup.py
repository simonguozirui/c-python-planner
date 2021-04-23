from setuptools import Distribution
import setuptools.command.build_ext as _build_ext
from distutils.core import setup, Extension
import sysconfig
from pathlib import Path
import sys, os
import subprocess

class build_ext(_build_ext.build_ext):
    def run(self):
            command = ["./build.sh", "-p", sys.executable]
            subprocess.check_call(command)

class BinaryDistribution(Distribution):
    def has_ext_modules(self):
        return True

def main():
    # Use the setup function we imported and set up the modules.
    # You may find this reference helpful: https://docs.python.org/3.6/extending/building.html
    # CFLAGS = ['-march=native', '-O3', '-pthread', '-Wall', '-Lbuild', '-lFrenetOptimalTrajectory']
    pwd = os.path.dirname(os.path.realpath(__file__))

    
    CFLAGS = ['-std=c++11', '-fPIC', '-shared', '-I', '-Ofast', '-pthread', '-Wall'] #  '-I/build'

    LDFLAGS = []
    # LDFLAGS = ['-l:libFrenetOptimalTrajectory.a']
    # LDFLAGS += ['-llibFrenetOptimalTrajectory']
    # LDFLAGS += ['-static']
    LDFLAGS += ['-Xlinker', '-export-dynamic']
    # LDFLAGS += ['-lstdc++', '-static-libstdc++']
    # LDFLAGS += ['-L' + '/usr/include/x86_64-linux-gnu/qt5/', '-lQtCore']

    LDFLAGS += ['-I', '/usr/include/x86_64-linux-gnu/qt5/QtCore', '-l' , 'Qt5Core']
    LDFLAGS += ['-L' + os.path.join(pwd, 'build'), '-lFrenetOptimalTrajectory']
    # LDFLAGS += ['-Wl,-Bstatic']
    # LDFLAGS += [os.path.join(pwd, 'build/libFrenetOptimalTrajectory.a')]
    # LDFLAGS += ['-L' + os.path.join(pwd, 'build'), '-Wl,-R'+os.path.join(pwd, 'build')]
    # LDFLAGS += ['-W','-Wno-undef', '-lstdc++', '-static-libstdc++', ] #'-lm'

    print("linker flag", LDFLAGS)

    #'AnytimeFrenetPlanner.cpp'
    module = Extension('fot_planner',
                    sources = ['planner_package.cpp'],
                    language='C++',
                    # include_dirs= ['/usr/include/x86_64-linux-gnu/qt5/'],
                    # libraries=['stdc++'],
                    extra_compile_args = CFLAGS, 
                    extra_link_args= LDFLAGS)
                    # extra_link_args = ['build/libFrenetOptimalTrajectory.so'])

    setup(name="fot_planner",
        version="1.0.0",
        description="FOT Planner",
        author="ERDOS Project",
        # cmdclass={"build_ext": build_ext})
        # distclass= BinaryDistribution,
        # package_data={'': ['build/libFrenetOptimalTrajectory.so']},
        ext_modules=[module])
        # include_package_data=True)

if __name__ == "__main__":
    main()