# ##############################################################################
#
# Configures the generation of DDL2CPP files

# This is used to generate the file during configure Needs to two separate
# execute_process to ensure the correct order
execute_process(
  COMMAND
    liquibase --headless=true --search-path ${PROJECT_SOURCE_DIR}/db/changelog/
    --changelog-file=db.changelog-root.yaml --url jdbc:h2:mem:test update-sql
    --output-file=${CMAKE_CURRENT_BINARY_DIR}/databaseddl.txt
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND_ERROR_IS_FATAL ANY)
execute_process(
  COMMAND ddl2cpp ${CMAKE_CURRENT_BINARY_DIR}/databaseddl.txt
          ${PROJECT_SOURCE_DIR}/src/database/schema openao::database
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND_ERROR_IS_FATAL ANY)

# This is used to generate the file during build (database changed)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/schema.h
  COMMAND
    liquibase --headless=true --search-path ${PROJECT_SOURCE_DIR}/db/changelog/
    --changelog-file=db.changelog-root.yaml --url jdbc:h2:mem:test update-sql
    --output-file=${CMAKE_CURRENT_BINARY_DIR}/databaseddl.txt
  COMMAND ddl2cpp ${CMAKE_CURRENT_BINARY_DIR}/databaseddl.txt
          ${PROJECT_SOURCE_DIR}/src/database/schema openao::database
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/db/changelog
  COMMENT "Generating database schema header"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_library(openao_database INTERFACE)
target_include_directories(openao_database
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
