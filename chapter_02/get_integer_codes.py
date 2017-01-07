# coding: utf-8
import sys


def bin_str(code):
    return bin(code)[2:]


def unary(x):
    return (bin_str(1), x)


def gamma(x):
    bx = bin_str(x)
    return (bx, 2 * len(bx) - 1)


def delta(x):
    bx_len = len(bin_str(x))
    (c, b) = gamma(bx_len)
    return (
        bin_str(x + ((int(c, 2) - 1) << (bx_len - 1))),
        bx_len - 1 + b,
    )


def code_str(code):
    return '{:0>{fill}}'.format(code[0], fill=code[1])


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
