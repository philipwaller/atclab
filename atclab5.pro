cache()

TEMPLATE = subdirs

SUBDIRS += \
    main \
    statemachine \
    pluginmanager \
    instructiontask \
    consenttask \
    scriptparser

main.depends = statemachine pluginmanager
