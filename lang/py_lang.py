import os.path as osp
from ._registry import ProgrammingLanguage, register_lang, TEMPLATE_ROOT


@register_lang('py')
class PythonLanguage(ProgrammingLanguage):
    @classmethod
    def matches_extension(cls, ext):
        return ext == 'py'

    @classmethod
    def requires_compilation(cls):
        return False

    @classmethod
    def execution_command(cls, source_file):
        return ['python3', source_file]

    @classmethod
    def compilation_command(cls, source_file):
        raise RuntimeError('Python does not require compilation')

    @classmethod
    def libraries(cls):
        return {
            'number': {'path': osp.join(TEMPLATE_ROOT, 'py/number_theory.py'), },
        }
