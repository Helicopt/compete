#!/home/toka/miniconda3/envs/TOKA/bin/python
import sys
import os
import os.path as osp
import argparse
import re
import yaml

TEMPLATE_ROOT = './templates'
CONTEST_ROOT = './contests'
CACHE_ROOT = './'

libs = {
    'py': {
        'number': {'path': osp.join(TEMPLATE_ROOT, 'py/number_theory.py'), },
    },
    'cpp': {
        'graph': {'path': osp.join(TEMPLATE_ROOT, 'cpp/graph.h'), },
        'number': {'path': osp.join(TEMPLATE_ROOT, 'cpp/number_theory.h'), },
        'seg': {'path': osp.join(TEMPLATE_ROOT, 'cpp/segment_tree.h'), },
        'trie': {'path': osp.join(TEMPLATE_ROOT, 'cpp/trie.h'), },
        'spfa': {'path': osp.join(TEMPLATE_ROOT, 'cpp/spfa.h'), 'dependency': 'graph', },
        'matrix': {'path': osp.join(TEMPLATE_ROOT, 'cpp/matrix.h'), },
        'bigint': {'path': osp.join(TEMPLATE_ROOT, 'cpp/bigint.h'), 'dependency': 'number', },
    },
}

styles = {
    'codeforces': {'shorts': ['cf'], 'default': 'py', 'templates': {
        'py': osp.join(TEMPLATE_ROOT, 'cf_template.py'),
        'cpp': osp.join(TEMPLATE_ROOT, 'cf_template.cpp'),
    }},
    'atcoder': {'shorts': ['at'], 'default': 'py', 'templates': {
        'py': osp.join(TEMPLATE_ROOT, 'at_template.py'),
        'cpp': osp.join(TEMPLATE_ROOT, 'at_template.cpp'),
    }},
    'google': {'shorts': ['gg'], 'default': 'py', 'templates': {
        'py': osp.join(TEMPLATE_ROOT, 'gg_template.py'),
        'cpp': osp.join(TEMPLATE_ROOT, 'gg_template.cpp'),
    }},
    'leetcode': {'shorts': ['lc'], 'default': 'py', 'templates': {
        'py': osp.join(TEMPLATE_ROOT, 'lc_template.py'),
        'cpp': osp.join(TEMPLATE_ROOT, 'lc_template.cpp'),
    }},
    'oi': {'shorts': ['oj'], 'default': 'cpp', 'templates': {
        'py': osp.join(TEMPLATE_ROOT, 'cf_template.py'),
        'cpp': osp.join(TEMPLATE_ROOT, 'cf_template.cpp'),
    }},
}


def get_style_names(styles):
    ret = {k: k for k in styles.keys()}
    for one in styles:
        for short in styles[one]['shorts']:
            ret[short] = one
    return ret


def next_tag(x):
    x = x.lower()
    r = ''
    for i in range(len(x)):
        i = len(x) - 1 - i
        if ord('a') <= ord(x[i]) < ord('z') or '0' <= x[i] < '9':
            return x[:i] + chr(ord(x[i]) + 1) + r
        elif x[i] == 'z':
            r = 'a' + r
        elif x[i] == '9':
            r = '0' + r
    return 'a' + r


def increase(name):
    if not isinstance(name, str):
        return None
    splits = name.split('_')
    return '{}_{}'.format(splits[0], next_tag(splits[1] if len(splits) > 1 else 'a'))


def get_default_cfg():
    return {
        'last': {'style': None, 'language': None, 'name': None, },
    }


def infer_from_last():
    cfg = osp.join(CACHE_ROOT, '.compete.yml')
    if not osp.exists(cfg):
        data = get_default_cfg()
        with open(cfg, 'w') as fd:
            yaml.safe_dump(data, fd)
    else:
        with open(cfg) as fd:
            data = yaml.safe_load(fd)
    return data['last']['style'], data['last']['language'], data['last']['name']


def save_last(style, language, name):
    cfg = osp.join(CACHE_ROOT, '.compete.yml')
    if not osp.exists(cfg):
        data = get_default_cfg()
        data.update(
            {'last': {'style': style, 'language': language, 'name': name}})
    else:
        with open(cfg) as fd:
            data = yaml.safe_load(fd)
        data['last']['style'], data['last']['language'], data['last']['name'] = style, language, name
    with open(cfg, 'w') as fd:
        yaml.safe_dump(data, fd)


def guess_contest(contest, styles):
    contest = contest.lower().strip()
    style, language, name = infer_from_last()
    lang = re.split(r'^[_\.]+', contest)[-1]
    if lang in libs:
        language = lang
    if re.match(r'[_]+', contest):
        return style, language, increase(name)
    if re.match(r'[\.]+', contest):
        return style, language, name
    name = contest
    for style_ in styles:
        for short in styles[style_]['shorts'] + [style_]:
            if contest.startswith(short):
                style = style_
                name = contest[len(short):]
    ext = name.split('.')[-1]
    if ext in libs:
        language = ext
        name = name[:-len(ext)-1]
    name = name.strip()
    while name.startswith('_'):
        name = name[1:]
    return style, language, name


def get_arguments(styles):
    style_names = get_style_names(styles)
    parser = argparse.ArgumentParser()
    parser.add_argument('contest', type=str)
    parser.add_argument('-s', '--style', type=str,
                        choices=list(style_names.keys()))
    parser.add_argument('-l', '--language', type=str)
    parser.add_argument('-n', '--name', type=str)
    parser.add_argument('-a', '--append', type=str, nargs='*')
    args = parser.parse_args()
    style, language, name = guess_contest(args.contest, styles)
    if args.name is None:
        args.name = name
    if args.style is None:
        args.style = style
    if args.style is not None:
        args.style = style_names[args.style]
    else:
        args.style = list(styles.keys())[0]
        print('No style found, use -s or --style to specify one')
        print('Available styles:', ', '.join(style_names.keys()))
        print('[Default] Currently used style:', args.style)
    if args.language is None:
        args.language = language
    if args.language is not None:
        assert args.language in styles[args.style]['templates'],\
            'Template not found for language {}, available: {}'.format(
            args.language, styles[args.style]['templates'].keys())
    else:
        args.language = styles[args.style]['default']
        print('No language found, use -l or --language to specify one')
        print('Available languages for {}:'.format(
            args.style), ', '.join(styles[args.style]['templates'].keys()))
        print('[Default] Currently used language:', args.language)
    assert args.name is not None and args.name.strip(
    ) != '', 'No name found and cannot infer one'
    return args


def load_lib(name: str, libs: dict, loaded: set) -> str:
    lib = libs[name]
    path = lib['path']
    if osp.exists(path):
        deps = lib.get('dependency', [])
        if isinstance(deps, str):
            deps = [deps]
        ret = ''
        for dep in deps:
            if dep in loaded:
                continue
            ret += load_lib(dep, libs, loaded)
        with open(path) as fd:
            ret += fd.read() + '\n'
        loaded.add(name)
        return ret
    else:
        return ''


def new_problem(args, styles, libs):
    template_path = styles[args.style]['templates'][args.language]
    problem_path = osp.join(CONTEST_ROOT, args.style, '{}.{}'.format(
        args.name, args.language))
    if not osp.exists(problem_path):
        os.makedirs(osp.dirname(problem_path), exist_ok=True)
        with open(template_path) as fdi, open(problem_path, 'w') as fdo:
            template = fdi.read()
            if args.append is not None:
                loaded = set()
                libstr = ''
                for one in args.append:
                    if one in libs[args.language]:
                        libstr += load_lib(one, libs[args.language], loaded)
                template = template.replace('{{libs}}', libstr)
            fdo.write(template)
    return problem_path


if __name__ == '__main__':
    args = get_arguments(styles)
    # print(args.style, args.language, args.name)
    _ = new_problem(args, styles, libs)
    save_last(args.style, args.language, args.name)
    print(_)
