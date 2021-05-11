disable_rtti()

set(SOURCES src/smtp.c)

new_library_static(smtp-client "${SOURCES}" "")

target_include_directories(smtp-client_static PUBLIC "src")

target_compile_definitions(smtp-client_static PUBLIC -DSMTP_OPENSSL)
target_link_libraries(smtp-client_static -lssl)
target_link_libraries(smtp-client_static -lcrypto)

set_target_properties(smtp-client_static PROPERTIES FOLDER Libraries)