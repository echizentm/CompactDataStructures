# coding: utf-8
import sys
import math


def check_kraft_mcmillan(bit_list):
    return sum(map(lambda bits: math.pow(2, -bits), bit_list)) <= 1


def shannon_entropy(probs):
    return sum(
        map(lambda p: -p*math.log2(p if p > 0 else 1), probs)
    )


def shannon_bits_list(probs):
    return list(
        map(lambda p: math.ceil(-math.log2(p if p > 0 else 1)), probs)
    )


def shannon_fano_codes(bits_list):
    code = 0b0
    prev_bits = 1
    codes = []
    for bits in bits_list:
        code <<= (bits - prev_bits)
        codes.append(code)
        prev_bits = bits
        code += 0b1
    return list(map(lambda code: bin(code)[2:], codes))


def average_code_length(codes, probs):
    length = 0
    for code, prob in zip(codes, probs):
        length += (len(code) * prob)
    return length


for line in sys.stdin:
    line = line.rstrip()
# line is comma separated probs (e.g. 0.6,0.3,0.05,0.025,0.025)
    probs = sorted(
        list(map(lambda x: float(x), line.split(','))),
        reverse=True,
    )
    bits_list = shannon_bits_list(probs)

    print('Probability list: {}'.format(probs))
    print('Bits(Code Length) list: {}'.format(bits_list))
    print('Satisfy Kraft-McMillan Inequality?: {}'.format(
        check_kraft_mcmillan(bits_list)
    ))
    print('Shannon Entropy: {}'.format(
        shannon_entropy(probs)
    ))
    print('Shannon-Fano Codes Length: {}'.format(
        average_code_length(shannon_fano_codes(bits_list), probs)
    ))
