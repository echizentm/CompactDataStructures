# coding: utf-8
import sys
from queue import PriorityQueue


class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right
        self.codes = []

    def __lt__(self, other):
        return self.value < other.value

    def huffman_codes(self, node, code):
        if node.left is None:
            self.codes.append(code)
        else:
            self.huffman_codes(node.left, code + '0')
            self.huffman_codes(node.right, code + '1')

    def __str__(self):
        self.codes = []
        self.huffman_codes(self, '')
        return 'value={}, codes={}'.format(self.value, self.codes)


def huffman_tree(probs):
    q = PriorityQueue()
    for p in probs:
        q.put(Node(p))
    while True:
        left = q.get()
        if q.empty():
            return left
        right = q.get()
        q.put(Node(
            left.value + right.value,
            left=left, right=right,
        ))


for line in sys.stdin:
    line = line.rstrip()
# line is comma separated probs or freqs (e.g. 5,2,2,1,1)
    probs = list(map(lambda x: float(x), line.split(',')))
    print(huffman_tree(probs))
