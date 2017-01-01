# coding: utf-8
import sys
import math


def shannon_ent(probs):
    return sum(
        map(lambda p: -p*math.log2(p if p > 0 else 1), probs)
    )


def seq2dic(seq):
    dic = {}
    for ch in seq:
        if ch in dic:
            dic[ch] += 1
        else:
            dic[ch] = 1
    return dic


def worst_case_ent(seq):
    return math.log2(len(seq2dic(seq)))


def zero_order_ent(seq):
    return shannon_ent(
        list(map(lambda v: v / len(seq), seq2dic(seq).values()))
    )


def high_order_ent(seq, k):
    dic = {}
    for i in range(0, len(seq) - k + 1):
        context = seq[i:i+k]
        ch = seq[i+k] if i+k < len(seq) else '$'
        if context in dic:
            dic[context] += ch
        else:
            dic[context] = ch
    return sum(
        map(lambda s: len(s) * zero_order_ent(s) / len(seq), dic.values())
    )


for line in sys.stdin:
    line = line.rstrip()
    print('String: {}'.format(line))
    print('Worst-Case Entropy: {}'.format(
        worst_case_ent(line)
    ))
    print('Zero-Order Empirical Entropy: {}'.format(
        zero_order_ent(line)
    ))
    print('First-Order Empirical Entropy: {}'.format(
        high_order_ent(line, 1)
    ))
    print('Second-Order Empirical Entropy: {}'.format(
        high_order_ent(line, 2)
    ))
