#!/usr/bin/python3
import random

def randchar():
    keyspace = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!£$%^&*()_-+=?><,.|\~#:;@'
    return random.choice(keyspace)

def sxor_bytes(s1, s2):
    return bytes(x ^ y for x, y in zip(str.encode(s1), str.encode(s2)))

"""xor hex strings

"""
def xor_hex_string(hs1, hs2):
    output = str_to_hex_string(s1) ^ str_to_hex(s2)
    return to_hex(output)

"""Convert a character string to a hex string
Iterate over characters in the input string and convert each character to a hex
string representation of it's ASCII code.
"""
def str_to_hex_string(string):
    return ''.join(hex(ord(c))[2:] for c in string)

"""Convert a string into a list of hex integers
This can be easier to reason about when performing logical operations on characters.
"""
def str_to_hex_list(string):
    result = []
    for c in string:
        result.append(hex(ord(c))[2:])
    return result

def strxor(a, b):
    len_ = min(len(a), len(b))
    return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a[:len_], b[:len_])])

def hex_string_to_ascii_characters(s):
    return bytearray.fromhex(s).decode()

def xor_hex_strings(s1, s2):
    return "".join('{:02X}'.format(x ^ y) for (x, y) in zip(bytearray.fromhex(s1), bytearray.fromhex(s2)))

def hex_string(s):
    return ''.join('{:02X}'.format(ord(char)) for char in s)

def random_character_hex(n):
    # Create a list of randomly-selected integers
    ints = [random.randint(32, 125) for item in range(n)]
    # Create a hexadecimal string from the integers
    hs = ''.join(['{:02X}'.format(int) for int in ints])
    return hs
