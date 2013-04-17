#!/usr/bin/env python

import threading

import spam


def grab_cores(threads=1, count=int(1e9)):
    _threads = []
    for i in range(threads):
        thread = threading.Thread(target=spam.busy, args=(count,))
        _threads.append(thread)
        thread.start()
    for thread in _threads:
        thread.join()


if __name__ == '__main__':
    import sys

    grab_cores(threads=int(sys.argv[1]))
