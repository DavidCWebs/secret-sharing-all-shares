#!/usr/bin/python3
from random import randint
from functools import reduce
from helpers import randchar
from helpers import str_to_hex_list
from helpers import random_character_hex
from helpers import xor_hex_strings

def main():
    secret = input("Enter secret:")
    nShares = input("Enter the required number of shares:")
    secretHexList = str_to_hex_list(secret)
    print("secretHexList: {}\n".format(''.join(str(e) for e in secretHexList)))

    # Create shares
    sharesDict = []
    for nShare in range(int(nShares) - 1):
        share = []
        for c in secretHexList:
            share.append(random_character_hex(1))
        sharesDict.append(share)

    xoredRandom = []
    for index in range(len(secretHexList)):
        xoredRandom.append(reduce(lambda i, j: xor_hex_strings(i, j), [s[index] for s in sharesDict]))
    finalRandom = [xor_hex_strings(i, j) for i, j in zip(xoredRandom, secretHexList)]

    print("\n")
    for index, share in enumerate(sharesDict):
        print("share-{}:".format(index), end = '\t')
        print(''.join(str(e) for e in share))
    print("combined:\t{}\n".format(''.join(str(e) for e in finalRandom)))

if __name__ == '__main__':
    main()
