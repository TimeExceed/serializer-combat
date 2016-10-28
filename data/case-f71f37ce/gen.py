#!/usr/bin/env python3

import random as rnd

STOP_LEVEL = 0.2
COUNT = 1000

def newInteger(fp):
    digit = rnd.randint(1, 9)
    fp.write('%d' % digit)
    for _ in range(17):
        nxt = rnd.random()
        if nxt < STOP_LEVEL:
            break
        digit = rnd.randint(0, 9)
        fp.write('%d' % digit)

if __name__ == '__main__':
    rnd.seed(12345)
    with open('case.dat', 'w') as fp:
        for i in range(COUNT):
            newInteger(fp)
            fp.write('\n')



