from distutils.core import setup, Extension
import sysconfig

def main():
    CFLAGS = ['-march=native', '-O3', '-pthread', '-Wall']

    module = Extension('fot_planner',
                    sources = ['planner_package.cpp', 'AnytimeFrenetPlanner.cpp'],
                    extra_compile_args = CFLAGS)

    setup(name="fot_planner",
        version="1.0.0",
        description="FOT Planner",
        author="ERDOS Project",
        ext_modules=[module])

if __name__ == "__main__":
    main()