
##DEFAULT_INCLUDES =
INCLUDES = $(TREE_BUILD_CXXFLAGS) $(BARRY_CFLAGS) $(BARRYBACKUP_CFLAGS) $(GTKMM_CFLAGS)
LIBS = $(TREE_BUILD_LDFLAGS) $(BARRY_LIBS) $(BARRYBACKUP_LIBS) $(GTKMM_LIBS)

AM_CXXFLAGS = -Wall -g
AM_CPPFLAGS = -DBARRYBACKUP_GLADEDIR='"$(gladedir)"'

# To use gettext
datadir = @datadir@
localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

dist_glade_DATA = \
	BackupWindow.glade \
	DatabaseSelectDlg.glade \
	PasswordDlg.glade \
	PromptDlg.glade \
	ConfigDlg.glade

bin_PROGRAMS = barrybackup

barrybackup_SOURCES = \
	main.cc \
	BackupWindow.cc \
	DatabaseSelectDlg.cc \
	PasswordDlg.cc \
	PromptDlg.cc \
	ConfigDlg.cc \
	DeviceBus.cc \
	DeviceIface.cc \
	Thread.cc \
	util.cc

noinst_HEADERS= \
	BackupWindow.h \
	ConfigDlg.h \
	DatabaseSelectDlg.h \
	DeviceBus.h \
	DeviceIface.h \
	PasswordDlg.h \
	PromptDlg.h \
	Thread.h \
	util.h \
	i18n.h \
	gettext.h

EXTRA_DIST = barry-gui.glade

