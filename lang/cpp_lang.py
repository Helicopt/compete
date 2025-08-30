import os.path as osp
from ._registry import ProgrammingLanguage, register_lang, TEMPLATE_ROOT


@register_lang('cpp')
class CppLanguage(ProgrammingLanguage):

    output_file = './sol'

    @classmethod
    def matches_extension(cls, ext):
        return ext in ['cpp', 'cc', 'cxx', 'c++']

    @classmethod
    def requires_compilation(cls):
        return True

    @classmethod
    def execution_command(cls, source_file):
        return [cls.output_file]

    @classmethod
    def compilation_command(cls, source_file):
        return ['g++', '-O2', '-std=c++17', '-o', cls.output_file, source_file]

    @classmethod
    def libraries(cls):
        return {
            'graph': {'path': osp.join(TEMPLATE_ROOT, 'cpp/graph.h'), },
            'number': {'path': osp.join(TEMPLATE_ROOT, 'cpp/number_theory.h'), },
            'seg': {'path': osp.join(TEMPLATE_ROOT, 'cpp/segment_tree.h'), },
            'trie': {'path': osp.join(TEMPLATE_ROOT, 'cpp/trie.h'), },
            'spfa': {'path': osp.join(TEMPLATE_ROOT, 'cpp/spfa.h'), 'dependency': 'graph', },
            'matrix': {'path': osp.join(TEMPLATE_ROOT, 'cpp/matrix.h'), },
            'bigint': {'path': osp.join(TEMPLATE_ROOT, 'cpp/bigint.h'), 'dependency': 'number', },
        }
