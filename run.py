#!/home/toka/miniconda3/envs/TOKA/bin/python
import argparse
import sys
import os
import subprocess

from lang import get_lang, list_langs


def run(path, ifd, ofd, efd):
    language = None
    lang_name = ''
    for lang in list_langs():
        L = get_lang(lang)
        if L.matches_extension(path.split('.')[-1]):
            language = L
            lang_name = lang
            break
    if language is None:
        print(f'No language found for extension {path.split(".")[-1]}')
        return -1
    print('Running {} using {} ({})'.format(
        path, language.__name__, lang_name))
    if language.requires_compilation():
        cp = subprocess.Popen(
            language.compilation_command(path), stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=efd)
        cp_code = cp.wait()
        if cp_code != 0:
            print('Compile Failed')
            return cp_code
    p = subprocess.Popen(
        language.execution_command(path), stdin=ifd, stdout=ofd, stderr=efd)
    ret = p.wait()
    return ret


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('path', type=str)
    parser.add_argument('-i', '--input', type=str)
    parser.add_argument('-o', '--output', type=str)
    args = parser.parse_args()
    ifd = sys.stdin
    ofd = sys.stdout
    efd = sys.stderr
    if args.input is not None and os.path.exists(args.input):
        ifd = open(args.input, 'r')
    if args.output is not None:
        ofd = open(args.output, 'w')
    if os.path.exists(args.path):
        ret_code = run(args.path, ifd, ofd, efd)
        if ret_code != 0:
            print('Run Failed')
        ifd.close()
        ofd.close()
        efd.close()
    else:
        print('File not found:', args.path)
