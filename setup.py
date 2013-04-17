from distutils.core import setup, Extension

spammify_module = Extension(
    'spammify',
    sources=['spammify.c'])

setup(
    name='Spammify',
    version='1.0',
    description='This is a spammify package',
    ext_modules=[spammify_module],
    )
