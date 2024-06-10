# This document is required.
## History
During World War I, the German Army used the ADFGVX cipher, which was manually applied in the field. It was used to send messages secretly via wireless telegraphy. The cipher is named after the six possible letters found in the ciphertext: A, D, F, G, V, and X. The letters were deliberately chosen because they differ greatly from one another in the Morse code. This reduced the risk of operator error. A French Army Lieutenant cryptanalyzed ADFGVX, which was broken in early June 1918. His method involved identifying messages with stereotyped beginnings, fractionating them, and then forming similar patterns in the ciphertext positions that corresponded to column headings in the transposition table. (After that step, extensive statistical analysis was required, which was completed entirely by hand.) It was thus only effective during periods of extremely high traffic, but this was also when the most important messages were sent.

## Cipher

The ADFGVX encryption uses a 6x6 square grid of 36 distinct characters. The following image is a basic grid I used for the program.

![image](https://github.com/Stuycs-K/final-project-09-arka-rahel/assets/113141652/1137c493-ba7d-45ec-852f-4031af96391d)

Perform a substitution by replacing each letter of the message by the corresponding pair of coordinates.

For example: BERLIN becomes AD,AV,FX,DX,DF,FD
This intermediate message will get another encryption by columnar transposition. The transposition uses a permutation key/keyphrase, usually based on a keyword. This can be found by rearranging its letters in alphabetic order. Two same letters are ranked in order of appearance, but if possible avoid duplicate letters in the keyphrase as this can lead to encryption/decryption ambiguities.
For example: The keyword CODE gives the transposition 1,3,4,2 because C(1),O(2),D(3),E(4) ranks alphabetically C(1),D(3),E(4),O(2) i.e. columns 1,3,4,2
The intermediate message is written by rows in a table whose width is the key size.

![image](https://github.com/Stuycs-K/final-project-09-arka-rahel/assets/113141652/0e2eae0e-3ca2-40bd-ab56-5910453a8776)

Columns are rearranged such as the permutation key.

![image](https://github.com/Stuycs-K/final-project-09-arka-rahel/assets/113141652/7a95b6b6-af6c-4b74-943e-4d574d09f458)

The ADFGVX final ciphertext is made by reading the letters of the table by columns starting from top to bottom and from left to right.

For example: The final encrypted message is AFDADFVXDDXF

The coded message is usually transmitted in Morse code to the recipient.
