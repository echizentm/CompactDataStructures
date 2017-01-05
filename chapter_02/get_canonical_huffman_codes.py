# coding: utf-8
import sys


def parse_text(text):
    dic = {}
    for symbol in text:
        if symbol in dic:
            dic[symbol] += 1
        else:
            dic[symbol] = 1
    return zip(
        *sorted(dic.items(), key=lambda item: item[1])
    )


def huffman_tree(freqs):
    nodes = []
    for f in freqs:
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


def code_lengths(nodes, depth, lengths):
    if nodes[1] is None:
        lengths.append(depth)
    else:
        code_lengths(nodes[1], depth + 1, lengths)
        code_lengths(nodes[2], depth + 1, lengths)


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


def bits_length(bits):
    return len(bin(bits)[2:])


def canonical_huffman_codes(text):
    [symbols, freqs] = parse_text(text)

    lengths = []
    code_lengths(huffman_tree(freqs), 0, lengths)
    codes = shannon_fano_codes(sorted(lengths))

    depth = bits_length(codes[-1])
    l_list = list(reversed(symbols))
    f_list = [None] * depth
    c_list = [None] * depth

    for i in range(len(codes) - 1, -1, -1):
        f_list[bits_length(codes[i]) - 1] = i
        c_list[bits_length(codes[i]) - 1] = codes[i]

    for i in range(len(f_list) - 1, -1, -1):
        if f_list[i] is None:
            f_list[i] = f_list[i + 1]
            c_list[i] = c_list[i + 1] >> 1

    return (l_list, f_list, c_list)


for line in sys.stdin:
    codes = canonical_huffman_codes(line.rstrip())
    print(codes)
