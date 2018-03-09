#!/usr/bin/python3
import sys
from functools import reduce
from helpers import xor_hex_strings
from helpers import hex_string_to_ascii_characters

def main(argv):
    if len(argv) <= 1:
        dataFilePath = input("Enter full path to data file:\n")
    elif len(argv) == 2:
        dataFilePath = argv[1]
    elif len(argv) > 2:
        sys.stderr.write("Usage: %s <full path to data file>\n" % (argv[0],))
        return 1

    # Collect shares: open data file and add lines to list
    with open(dataFilePath) as f:
        shares = [line.rstrip('\n') for line in f]

    for fragment in shares:
        print("Fragment: {}, Type: {}".format(fragment, type(fragment)))

    # Combine shares
    xorAllShares = []
    xorAllShares.append(reduce(lambda i, j: xor_hex_strings(i, j), shares))

    # Output
    print("\n")
    decryptedAsciiString = hex_string_to_ascii_characters(''.join(str(e) for e in xorAllShares))
    print("Decrypted: {}\n".format(decryptedAsciiString))

if __name__ == '__main__':
    sys.exit(main(sys.argv))
