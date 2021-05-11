disable_rtti()

file(GLOB_RECURSE SOURCES *.cpp *.h)

if(MSVC)
	precompiled_header(pch)
endif()

new_library_shared(mod_smtp "${SOURCES}" "")

# Link with SMTP-Client
target_link_libraries(mod_smtp smtp-client_static)

INCLUDE_DIRECTORIES("../smtp-client/src")

set_target_properties(mod_smtp PROPERTIES FOLDER Modules)