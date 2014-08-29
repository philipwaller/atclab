
TEMPLATE = subdirs
SUBDIRS += \
    statemachine \
    pluginmanager \
    instructiontask \
    consenttask \
    scriptreader

message("!")
message("!  $${_PRO_FILE_}")
message("!  subdir: $${SUBDIRS}")
message("!")
