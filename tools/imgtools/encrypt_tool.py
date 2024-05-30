#! /usr/bin/env python3
import os

class encrypt_tool_err(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

def load_aes_key(aes_keyfile_name):
  aes_file = open("{}".format(aes_keyfile_name),"rb+")
  aes_key = aes_file.read()
  aes_file.close()

  return aes_key

def encrypt_with_aes_openssl(aes_key, plaintext_file_name, ciphertext_file_name):
    openssl_cmd = "openssl enc -aes-256-ecb -e -in {} -out {} -K {} --nopad".format(
                    plaintext_file_name, ciphertext_file_name, aes_key.hex())
    os.system(openssl_cmd)

def decrypt_with_aes_openssl(aes_key, ciphertext_file_name, plaintext_file_name):
    openssl_cmd = "openssl enc -aes-256-ecb -d -in {} -out {} -K {} --nopad".format(
                    ciphertext_file_name, plaintext_file_name, aes_key.hex())
    os.system(openssl_cmd)

def encrypt_with_aes(aes_key, plaintext_file_name, ciphertext_file_name):
    if os.system("openssl version") == 0:
        encrypt_with_aes_openssl(aes_key, plaintext_file_name, ciphertext_file_name)
    else:
        raise encrypt_tool_err("openssl is not avaiable!")

def decrypt_with_aes(aes_key, ciphertext_file_name, plaintext_file_name):
    if os.system("openssl version") == 0:
        decrypt_with_aes_openssl(aes_key, ciphertext_file_name, plaintext_file_name)
    else:
        raise encrypt_tool_err("openssl is not avaiable!")

import argparse
#The function to parse the input parameters
def parse_input_args():
    parser = argparse.ArgumentParser(description="generate key data an store into Mysql")

    parser.add_argument('--version', '-v', action='version', version='%(prog)s version : v 0.01',
                        help='show the version')

    parser.add_argument('--debug', '-d', action='store_true',
                        help='show the debug info')
    group = parser.add_mutually_exclusive_group()

    group.add_argument('--encrypt', '-en', action='store_true',
                        help='encryped the input file')

    group.add_argument('--dencrypt', '-de', action='store_true',
                        help='the input file to be encryped')

    parser.add_argument('--keyfile', '-k', nargs=1, required= True,
                        help='dencrypt the input file')

    parser.add_argument('--inputfile', '-i', nargs=1, required= True,
                        help='the input file to be encryped')

    parser.add_argument('--outputfile', '-o', nargs=1, required= True,
                        help='the output file to be stored')

    args = parser.parse_args()

    return args

def main():
    args = parse_input_args()

    ##check the input files
    if os.path.exists(args.keyfile[0]) is not True:
        raise encrypt_tool_err("keyfile: {} is NOT exist!".format(args.keyfile[0]))
    if os.path.exists(args.inputfile[0]) is not True:
        raise encrypt_tool_err("inputfile: {} is NOT exist!".format(args.inputfile[0]))

    if args.debug is True:
        print("keyfile: {}".format(args.keyfile[0]))
        print("inputfile: {}".format(args.inputfile[0]))
        print("outputfile: {}".format(args.outputfile[0]))

    aes_key = load_aes_key(args.keyfile[0])
    if args.debug is True:
        print("aes_key: {}".format(aes_key.hex()))

    if args.encrypt is True:
        encrypt_with_aes(aes_key, args.inputfile[0], args.outputfile[0])

    if args.dencrypt is True:
        decrypt_with_aes(aes_key, args.inputfile[0], args.outputfile[0])

##The main function
if __name__ == "__main__":
    main()
