
class ProgrammingLanguage:

    @classmethod
    def matches_extension(cls, ext: str) -> bool:
        raise NotImplementedError

    @classmethod
    def requires_compilation(cls) -> bool:
        raise NotImplementedError

    @classmethod
    def execution_command(cls, source_file) -> list[str]:
        raise NotImplementedError

    @classmethod
    def compilation_command(cls, source_file) -> list[str]:
        raise NotImplementedError

    @classmethod
    def libraries(cls) -> dict[str, dict]:
        return {}


global lang_libs
lang_libs = {}

global TEMPLATE_ROOT
TEMPLATE_ROOT = './templates'


def register_lang(obj):
    if isinstance(obj, str):
        def wrapper(cls):
            if not issubclass(cls, ProgrammingLanguage):
                raise TypeError(
                    'Can only register subclass of ProgrammingLanguage')
            if obj in lang_libs:
                raise KeyError('Language {} already registered'.format(obj))
            lang_libs[obj] = cls
            return cls
        return wrapper
    else:
        cls = obj
        if not issubclass(cls, ProgrammingLanguage):
            raise TypeError(
                'Can only register subclass of ProgrammingLanguage')
        if cls.__name__ in lang_libs:
            raise KeyError(
                'Language {} already registered'.format(cls.__name__))
        lang_libs[cls.__name__] = cls
        return cls


def get_lang(name: str) -> ProgrammingLanguage:
    if name not in lang_libs:
        raise KeyError('Language {} not registered'.format(name))
    return lang_libs[name]


def list_langs() -> list[str]:
    return list(lang_libs.keys())
