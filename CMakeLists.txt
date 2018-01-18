cmake_minimum_required(VERSION 3.8)
project(Project)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_STEMMER stemming/stemming_oleander/stemming.h stemming/stemming_oleander/english_stem.h stemming/indexing/string_util.h stemming/utilities/safe_math.h stemming/indexing/common_lang_constants.h stemming/utilities/debug_logic.h stemming/utilities/utilities.h)
set(SOURCE_FILES main.cpp stemmer.cpp SPIMI.cpp SPIMI.h Parser.cpp Parser.h StopWords.cpp StopWords.h)

set(EXPATSOURCE expath/loadlibrary.c expath/xmlparse.c expath/xmlrole.c expath/xmltok.c expath/xmltok_impl.c expath/xmltok_ns.c)
set(EXPATHEADERS expath/ascii.h expath/asciitab.h expath/expat.h expath/expat_external.h expath/iasciitab.h expath/internal.h expath/latin1tab.h expath/nametab.h expath/siphash.h expath/utf8tab.h expath/winconfig.h expath/xmlrole.h expath/xmltok.h expath/xmltok_impl.h expath/ExpatImpl.h)

add_executable(IRProject ${SOURCE_FILES} ${SOURCE_STEMMER} ${EXPATSOURCE} ${EXPATHEADERS})
