# Example: Marian as a library

[![Ubuntu](../../actions/workflows/ubuntu.yml/badge.svg)](../../actions/workflows/ubuntu.yml)
[![MacOS](../../actions/workflows/macos.yml/badge.svg)](../../actions/workflows/macos.yml)
[![Windows](../../actions/workflows/windows.yml/badge.svg)](../../actions/workflows/windows.yml)

This repository serves as a minimal example of a CMake project with a [marian][marian]
dependency. The dependency to Marian is facilitated by a submodule to [marian-dev].

## Usage

Acquiring a copy of this repository can be done with the "[Use this template][template]" button, which generates a new repository with the same structure and content.

Alternatively, you can clone it locally via
```shell
git clone https://github.com/marian-nmt/marian-example-library
cd marian-example-library
```

### Compile
```shell
mkdir build
cd build
cmake ..
cmake --build .
```

### Run
```shell
./example
```

## About this example
The code in [src/main.cpp](src/main.cpp) builds a simple expression graph using Marian. It mirrors the example found in Marian's [developer documentation][dev_docs].

The expression graph represents `z = x*y + sin(x)`, with an absolute-error applied to `z` as a loss function. It performs a forward and backward evaluation of the graph, and a single update of the graph parameters from a `Stochastic Gradient Descent` optimizer. Following the example, `x` takes the place of a learnable parameter.

After the parameter update, the graph parameters are saved to `example-model.npz`. You can inspect its contents with [`script/read-npz.py`](/script/read-npz.py).

Please refer to the [marian][marian] project for further documentation.

## About this repository
There are example CI builds available for
  - Ubuntu
  - MacOS
  - Windows

These compile and run the example executable.

Additionally, the Marian submodule is updatable via dependabot.

## Acknowledgements
The development of Marian received funding from the European Union's
_Horizon 2020 Research and Innovation Programme_ under grant agreements
688139 ([SUMMA](http://www.summa-project.eu); 2016-2019),
645487 ([Modern MT](http://www.modernmt.eu); 2015-2017),
644333 ([TraMOOC](http://tramooc.eu/); 2015-2017),
644402 ([HiML](http://www.himl.eu/); 2015-2017),
825303 ([Bergamot](https://browser.mt/); 2019-2021),
the European Union's Connecting Europe Facility project
2019-EU-IA-0045 ([User-focused Marian](https://marian-project.eu); 2020-2022),
the Amazon Academic Research Awards program,
the World Intellectual Property Organization,
and is based upon work supported in part by the Office of the Director of
National Intelligence (ODNI), Intelligence Advanced Research Projects Activity
(IARPA), via contract #FA8650-17-C-9117.

This software contains source code provided by NVIDIA Corporation.

<!-- Links -->
[marian]: https://marian-nmt.github.io/
[marian-dev]: https://github.com/marian-nmt/marian-dev
[dev_docs]: https://marian-nmt.github.io/docs/api/graph.html
[template]: https://github.com/marian-nmt/marian-example-library/generate
