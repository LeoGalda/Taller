import struct

#bits = "00010000000000000000101101011011"
#int_value = int(bits, base=2)
str_value = "10000b5b"
int_value = int(str_value, base=16)

bin_array = struct.pack('>I', int_value)
with open("test.bin", "wb") as f:
    f.write(bin_array)
