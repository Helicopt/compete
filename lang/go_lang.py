from ._registry import ProgrammingLanguage, register_lang


@register_lang('go')
class GoLanguage(ProgrammingLanguage):

    output_file = './sol'

    @classmethod
    def matches_extension(cls, ext):
        return ext == 'go'

    @classmethod
    def requires_compilation(cls):
        return True

    @classmethod
    def execution_command(cls, source_file):
        return [cls.output_file]

    @classmethod
    def compilation_command(cls, source_file):
        return ['go', 'build', '-o', cls.output_file, source_file]
