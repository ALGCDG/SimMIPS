When loading into registers, 'endianness' makes no sense. A word in memory has a particular int
value that could describe it. Loading into a register simply transfers the int value.

LWL and LWR
These are used for unaligned memory access.
-   LWL is called so as it loads the 'left' part (most sig) into the top end of a register.
    -For example if the LWL is given an address and no additional offset, it will simply
    load the entire word correctly into memory.
    -Increasing this offset moves the point at which the alignment starts.
    -An offset of one means that the data loaded into the register starts from the next byte
    in memory (the second most significant byte) and loads the 3 bytes from that point into
    the upper part of the register, leaving the bottom byte as it was.

    LWL OR LWR DO NOT OVERWRITE THE DATA IN THE REGISTER FOR THE BYTES NOT LOADED IN.
