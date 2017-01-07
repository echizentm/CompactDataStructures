# coding: utf-8
import sys


def unary(x):
    return (1, x)


def gamma(x):
    return (x, 2 * x.bit_length() - 1)


def delta(x):
    (c, b) = gamma(x.bit_length())
    return (
        x + ((c - 1) << (x.bit_length() - 1)),
        x.bit_length() - 1 + b,
    )


def code_str(code):
    return '{:0>{fill}}'.format(bin(code[0])[2:], fill=code[1])


for line in sys.stdin:
    print('Unary Code: {}'.format(
        code_str(unary(int(line)))
    ))
    print('Gamma Code: {}'.format(
        code_str(gamma(int(line)))
    ))
    print('Delta Code: {}'.format(
        code_str(delta(int(line)))
    ))
