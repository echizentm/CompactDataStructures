# coding: utf-8
import sys
from bisect import bisect


def parse_text(text):
    dic = {}
    for symbol in text:
        if symbol in dic:
            dic[symbol] += 1
        else:
            dic[symbol] = 1
    return zip(
        *sorted(dic.items(), reverse=True, key=lambda item: item[1])
    )


def huffman_tree(freqs):
    nodes = []
    for f in sorted(freqs):
        nodes.append((f, None, None))

    insert_pos = 0
    while len(nodes) > 1:
        left = nodes.pop(0)
        right = nodes.pop(0)
        insert_pos = max(insert_pos - 2, 0)
        new_node = (left[0] + right[0], left, right)
        while (
            insert_pos < len(nodes) and
            nodes[insert_pos][0] <= new_node[0]
        ):
            insert_pos += 1
        nodes.insert(insert_pos, new_node)
    return nodes[0]


def rec_code_lengths(nodes, depth, lengths):
    if nodes[1] is None:
        lengths.append(depth)
    else:
        rec_code_lengths(nodes[1], depth + 1, lengths)
        rec_code_lengths(nodes[2], depth + 1, lengths)


def code_lengths(nodes):
    lengths = []
    rec_code_lengths(nodes, 0, lengths)
    return sorted(lengths)


def shannon_fano_codes(lengths):
    code = 0b0
    prev_length = 1
    codes = []
    for length in lengths:
        code <<= (length - prev_length)
        codes.append(code)
        prev_length = length
        code += 0b1
    return codes


def canonical_huffman_codes(symbols, lengths):
    codes = shannon_fano_codes(lengths)

    max_depth = lengths[-1]
    l_list = symbols
    f_list = [None] * max_depth
    c_list = [None] * max_depth
    c2_list = [None] * max_depth

    for i in range(len(codes) - 1, -1, -1):
        pos = lengths[i] - 1
        f_list[pos] = i
        c_list[pos] = codes[i]
        c2_list[pos] = codes[i] << (max_depth - pos - 1)

    for i in range(len(f_list) - 1, -1, -1):
        if f_list[i] is None:
            f_list[i] = f_list[i + 1]
            c_list[i] = c_list[i + 1] >> 1
            c2_list[i] = c2_list[i + 1]

    return (l_list, f_list, c_list, c2_list)


def canonical_huffman_codes_from_text(text):
    [symbols, freqs] = parse_text(text)
    lengths = code_lengths(huffman_tree(freqs))
    return canonical_huffman_codes(symbols, lengths)


def decode(codes, text):
    (l_list, f_list, c_list, c2_list) = codes
    max_depth = len(f_list)

    text_tmp = text + '0' * max_depth
    pos = 0
    decoded = ''
    while pos < len(text):
        num = int(text_tmp[pos:pos+max_depth], 2)
        depth = bisect(c2_list, num)
        decoded += l_list[
            f_list[depth - 1] +
            (num >> (max_depth - depth)) -
            c_list[depth - 1]
        ]
        pos += depth
    return decoded


# Compact Data Structures (p.28, example 2.16)
codes = canonical_huffman_codes(
    list('abcdefghijklmnop'),
    [2, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5],
)
print('Canonical Huffman Codes: {}'.format(codes))

for line in sys.stdin:
    # line is bit sequence as string (cf. '1000010101')
    print(decode(codes, line.rstrip()))
