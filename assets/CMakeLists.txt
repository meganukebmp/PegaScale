project(bundlejs)

add_custom_target(GenAssets DEPENDS generate_bundlejs)

add_custom_target(npmtarget)
add_custom_command(
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND npm install ${PROJECT_SOURCE_DIR}/exploit/
    TARGET npmtarget
)

add_custom_target(generate_bundlejs DEPENDS npmtarget)
add_custom_command(
    COMMAND npx browserify ${PROJECT_SOURCE_DIR}/exploit/main.js -o ../www/bundle.js
    TARGET generate_bundlejs
)

add_custom_command(
    TARGET GenAssets PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/static ../www
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/payloads ../www/payloads
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/scripts/ ../www/scripts
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/exploit/minmain_1.0.0-4.1.0.js ../www/
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/exploit/minmain_5.0.0-6.0.1.js ../www/
)