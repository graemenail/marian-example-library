#!/usr/bin/env python3
import numpy as np
import sys


def main():
    if len(sys.argv) != 2:
        print("Usage: {0} model.npz".format(*sys.argv))
        exit(1)

    filename = sys.argv[1]
    with np.load(filename) as model:
        keys = model.files
        print(f"Inspecting {filename}, with {len(keys)} parameters")
        for k in keys:
            param = model[k]
            print(f"Parameter: {k}, shape={param.shape}", param, sep="\n")


if __name__ == "__main__":
    main()
