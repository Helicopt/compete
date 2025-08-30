import os
import sys
from compete import styles, CONTEST_ROOT
from lang import list_langs, get_lang


def archive(sol):
    origin = sol
    sol = os.path.basename(sol).lower()
    splits = sol.split('_')
    if len(splits) <= 1:
        return
    name = splits[0]
    p = '_'.join(splits[1:])
    tar = os.path.join(os.path.dirname(origin), name, p)
    tar_dir = os.path.dirname(tar)
    if not os.path.exists(tar_dir):
        os.makedirs(tar_dir, exist_ok=True)
    if os.path.exists(tar):
        print('not moving {} to {} because it already exists'.format(origin, tar))
    else:
        os.rename(origin, tar)
        print('moving {} to {}'.format(origin, tar))


def check_extension(sol: str) -> bool:
    return any([get_lang(lang).matches_extension(sol.split('.')[-1]) for lang in list_langs()])


if __name__ == '__main__':
    if len(sys.argv) > 1:
        CONTEST_ROOT = sys.argv[1]
        styles = ['']
    for style in styles:
        style_dir = os.path.join(CONTEST_ROOT, style)
        if not os.path.exists(style_dir):
            continue
        all_sols = [os.path.join(style_dir, f) for f in os.listdir(style_dir)]
        for sol in all_sols:
            if os.path.isfile(sol) and check_extension(sol):
                archive(sol)
