cache()

TEMPLATE = subdirs

SUBDIRS += \
    main \
    statemachine \
    pluginmanager \
    instructiontask \
    consenttask \
    scriptreader

main.depends = statemachine pluginmanager
