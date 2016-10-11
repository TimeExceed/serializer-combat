#!/usr/bin/env python3

import random as rnd

COUNT = 1000
LEN = 16
ALPHABET = '0123456789ABCDEF'

def newBytes(fp):
    for _ in range(LEN):
        digit = rnd.choice(ALPHABET)
        fp.write(digit)

if __name__ == '__main__':
    rnd.seed(12345)
    with open('case.dat', 'w') as fp:
        for i in range(COUNT):
            newBytes(fp)
            fp.write('\n')



