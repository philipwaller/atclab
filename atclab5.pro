cache()

TEMPLATE = subdirs

SUBDIRS += \
    main \
    statemachine \
    pluginmanager \
    instructiontask \
    consenttask

main.depends = statemachine pluginmanager
