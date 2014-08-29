cache()

TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    src \
    tst \
    app

app.depends = src
tst.depends = src


message("|-------------------------------------------------------------------------------")
message("|  .qmake.conf")
message("|")
message("|  PRJDIR = $${PRJDIR}")
message("|  APPDIR = $${APPDIR}")
message("|  SRCDIR = $${SRCDIR}")
message("|  TSTDIR = $${TSTDIR}")
message("|")
message("|  OUTDIR = $${OUTDIR}")
message("|  DISTDIR = $${DISTDIR}")
message("|  PLUGIN = $${PLUGIN}")
message("|")
message("|  CURRENT_VERSION = $${CURRENT_VERSION}")
message("|")
message("|-------------------------------------------------------------------------------")

message("!")
message("!  $${_PRO_FILE_}")
message("!")
