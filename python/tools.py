#!/usr/bin/env python
# coding=utf-8

###
# Base on argument to select function to run
###
import argparse
import template

parser = argparse.ArgumentParser(description='test')
parser.add_argument('--func', default='0', type=str, help='chose one func')
parser.add_argument('input', nargs='*', help='input parmeter')

if __name__ == '__main__':
    print('OpenCV')
    args = parser.parse_args()
    getattr(template, 'func'+args.func)(*args.input)


###
#
###
