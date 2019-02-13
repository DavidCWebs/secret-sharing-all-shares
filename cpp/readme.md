Secret Sharing All Shares Required
==================================
This is a [trivial secret sharing][2] implementation - every share is required to rebuild the original secret. 
This shouldn't be confused wtih an efficient secret sharing such as [Shamir's Secret Sharing Scheme][3] whereby a threshold number of shares less than the total number of shares is required for reconstruction.

C++ Implementation
------------------
User is prompted to enter a secret and the number of shares(n) that are required.

Vectors of random bytes are generated using the `gcry_randomize` function of [libgcrypt][1], with the `GCRY_STRONG_RANDOM` flag. Each vector has the same number of bytes as the secret, and n - 1 vectors of random bytes are generated.

A final share vector is generated that consists of unsigned chars that result from (`secret` XOR `share₀` XOR `share₁` XOR ... XOR `shareₙ₋₁`) performed on a character-by-character basis.

Generate Shares
---------------
* Run `make`.
* Run `./bin/split`

Output of Shares
----------------
To ouput the shares as printable strings, each byte is represented as a two-character hex string.

Example:

```
$ ./bin/split
Please enter the secret that should be split:
david
Enter the number of fragments into which the secret should be split:
5
Shares
+------------+
| AA7DD25300 |
+------------+
| 27D05D1600 |
+------------+
| 70BAEE1400 |
+------------+
| B6182CC100 |
+------------+
| 2F6E3BF964 |
+------------+
```

Secret Recovery
---------------
* Create a manifest file with each share on a separate line. 
* Run `./bin/combine`.
* Enter the full path to the manifest file when prompted.

The secret is recovered by XORing all shares on a character-by-character basis. 

Taking the above example, the result of XORing the first byte of each share is determined by `0xAA ^ 0x27 ^ 0x70 ^ 0xB6 ^ 0x2F = (decimal)100`. This is the ascii representation of the character 'd', which is the first character of the original secret.

References
----------
* [Trivial secret sharing][2]
* [Libgcrypt][1]


[1]: https://www.gnupg.org/related_software/libgcrypt/
[2]: https://en.wikipedia.org/wiki/Secret_sharing#Trivial_secret_sharing
[3]: https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing
