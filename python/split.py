#!/usr/bin/python3
from random import randint
from functools import reduce
from helpers import randchar
from helpers import str_to_hex_list
from helpers import random_character_hex
from helpers import xor_hex_strings


DEBUG = 1

def main():
    secret = input("Enter secret:")
    n_shares = input("Enter the required number of shares:")
    secret_hex_list = str_to_hex_list(secret)
#    print("secret_hex_list: {}\n".format(''.join(str(e) for e in secret_hex_list)))

    # Create shares
    shares_dict = []
    for nShare in range(int(n_shares) - 1):
        share = []
        for c in secret_hex_list:
            share.append(random_character_hex(1))
        shares_dict.append(share)

    xored_random = []
    for index in range(len(secret_hex_list)):
        xored_random.append(reduce(lambda i, j: xor_hex_strings(i, j), [s[index] for s in shares_dict]))
    final_random = [xor_hex_strings(i, j) for i, j in zip(xored_random, secret_hex_list)]

    for index, share in enumerate(shares_dict):
        print("share-{}:".format(index), end = '\t')
        print(''.join(str(e) for e in share))
    print("combined:\t{}\n".format(''.join(str(e) for e in final_random)))
    
    if DEBUG:
        with open('shares.txt', 'wt') as f:
            for share in shares_dict:
                f.write(''.join(str(c) for c in share) + '\n')
            f.write(''.join(str(c) for c in final_random) + '\n')

if __name__ == '__main__':
    main()
