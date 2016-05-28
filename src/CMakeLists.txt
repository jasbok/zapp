# Collect all source files
list(APPEND SOURCES
  "analysers/dosbox_config_analyser.cpp"
  "analysers/name_analyser.cpp"
  "analysers/target_analyser.cpp"
  "analysers/type_analyser.cpp"

  "configs/config.cpp"

  "executors/executor.cpp"
  "executors/executor_dosbox.cpp"
  "executors/executor_factory.cpp"

  "extractors/extractor.cpp"
  "extractors/extractor_innoextract.cpp"
  "extractors/extractor_librar.cpp"
  "extractors/extractor_libarchive.cpp"
  "extractors/extractor_factory.cpp"

  "libs/libarchive.cpp"
  "libs/librar.cpp"

  "menus/menu.cpp"

  "patchers/patcher.cpp"
  "patchers/patcher_copy.cpp"

  "processes/innoextract.cpp"
  "processes/dosbox.cpp"

  "sanitisers/sanitiser.cpp"
  "sanitisers/dosbox_sanitiser.cpp"
)

add_executable(zapp "main.cpp" ${SOURCES})
target_link_libraries(zapp ${TARGET_LINK_LIBS})
