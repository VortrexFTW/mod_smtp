disable_rtti()

set(SOURCES src/smtp.c)

new_library_static(smtp-client "${SOURCES}" "")

target_include_directories(smtp-client PUBLIC "src")

target_link_libraries(smtp-client -lssl)
target_link_libraries(smtp-client -lcrypto)

set_target_properties(smtp-client PROPERTIES FOLDER Libraries)