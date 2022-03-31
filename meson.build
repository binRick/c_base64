#//***********************************************************/
project(
    'c_base64',          ['c'],         version : '0.0.1',         
    default_options : ['warning_level=2','c_std=gnu99'],
)
#//***********************************************************/
host_system = host_machine.system()

cc = meson.get_compiler('c')
sh = find_program('sh', required : true)
passh = find_program('passh', required : true)

#//***********************************************************/
test_deps = []
#//***********************************************************/
incdir = include_directories(
  './include', 
  './deps', 
  '../',
  '../metalang99/include',
  '../ok',
)
#//***********************************************************/
test_base64_module3 = executable('test_base64_module3', [ 
    'src/base64.c', 
    'tests/test_base64_module3.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_base64_module2 = executable('test_base64_module2', [ 
    'src/base64.c', 
    'tests/test_base64_module2.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_base64_module1 = executable('test_base64_module1', [ 
    'src/base64.c', 
    'tests/test_base64_module1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_base64_module4 = executable('test_base64_module4', [ 
    'src/base64.c', 
    'tests/test_base64_module4.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_base64_module6 = executable('test_base64_module6', [ 
    'src/base64.c', 
    'tests/test_base64_module6.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_base64_module5 = executable('test_base64_module5', [ 
    'src/base64.c', 
    'tests/test_base64_module5.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
#//***********************************************************/
tests = [
  ['test base64 module 1', test_base64_module1, 'test-base64-module1.log'],
  ['test base64 module 2', test_base64_module2, 'test-base64-module2.log'],
  ['test base64 module 3', test_base64_module3, 'test-base64-module3.log'],
  ['test base64 module 4', test_base64_module4, 'test-base64-module4.log'],
  ['test base64 module 5', test_base64_module5, 'test-base64-module5.log'],
  ['test base64 module 6', test_base64_module6, 'test-base64-module6.log'],
]
#//***********************************************************/

#//***********************************************************/
test_env = environment()
test_env.set('__SH', sh.full_path())
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
foreach i : tests
test(i[0], passh, args: ['-L', i[2], i[1] ], env: test_env)
endforeach
#//***********************************************************/


