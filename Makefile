#############################################################################
# Makefile for building: Lab2_server
# Generated by qmake (2.01a) (Qt 4.8.4) on: ?? 12. ??? 15:29:21 2015
# Project:  Lab2_server.pro
# Template: app
# Command: c:\Qt\4.8.4.1\bin\qmake.exe -spec c:\Qt\4.8.4.1\mkspecs\win32-g++ CONFIG+=release -o Makefile Lab2_server.pro
#############################################################################

first: release
install: release-install
uninstall: release-uninstall
MAKEFILE      = Makefile
QMAKE         = c:\Qt\4.8.4.1\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = del
SYMLINK       = 
DEL_DIR       = rmdir
MOVE          = move
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
SUBTARGETS    =  \
		release \
		debug

release: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_default: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-make_first: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release first
release-all: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_default: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-make_first: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug first
debug-all: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: Lab2_server.pro  c:/Qt/4.8.4.1/mkspecs/win32-g++/qmake.conf c:/Qt/4.8.4.1/mkspecs/features/device_config.prf \
		c:/Qt/4.8.4.1/mkspecs/qconfig.pri \
		c:/Qt/4.8.4.1/mkspecs/modules/qt_webkit_version.pri \
		c:/Qt/4.8.4.1/mkspecs/features/qt_functions.prf \
		c:/Qt/4.8.4.1/mkspecs/features/qt_config.prf \
		c:/Qt/4.8.4.1/mkspecs/features/exclusive_builds.prf \
		c:/Qt/4.8.4.1/mkspecs/features/default_pre.prf \
		c:/Qt/4.8.4.1/mkspecs/features/win32/default_pre.prf \
		c:/Qt/4.8.4.1/mkspecs/features/release.prf \
		c:/Qt/4.8.4.1/mkspecs/features/debug_and_release.prf \
		c:/Qt/4.8.4.1/mkspecs/features/default_post.prf \
		c:/Qt/4.8.4.1/mkspecs/features/win32/default_post.prf \
		c:/Qt/4.8.4.1/mkspecs/features/win32/rtti.prf \
		c:/Qt/4.8.4.1/mkspecs/features/win32/exceptions.prf \
		c:/Qt/4.8.4.1/mkspecs/features/win32/stl.prf \
		c:/Qt/4.8.4.1/mkspecs/features/shared.prf \
		c:/Qt/4.8.4.1/mkspecs/features/warn_on.prf \
		c:/Qt/4.8.4.1/mkspecs/features/qt.prf \
		c:/Qt/4.8.4.1/mkspecs/features/win32/thread.prf \
		c:/Qt/4.8.4.1/mkspecs/features/moc.prf \
		c:/Qt/4.8.4.1/mkspecs/features/win32/windows.prf \
		c:/Qt/4.8.4.1/mkspecs/features/resources.prf \
		c:/Qt/4.8.4.1/mkspecs/features/uic.prf \
		c:/Qt/4.8.4.1/mkspecs/features/yacc.prf \
		c:/Qt/4.8.4.1/mkspecs/features/lex.prf \
		c:/Qt/4.8.4.1/mkspecs/features/include_source_dir.prf \
		c:/Qt/4.8.4.1/lib/qtmain.prl
	$(QMAKE) -spec c:\Qt\4.8.4.1\mkspecs\win32-g++ CONFIG+=release -o Makefile Lab2_server.pro
c:\Qt\4.8.4.1\mkspecs\features\device_config.prf:
c:\Qt\4.8.4.1\mkspecs\qconfig.pri:
c:\Qt\4.8.4.1\mkspecs\modules\qt_webkit_version.pri:
c:\Qt\4.8.4.1\mkspecs\features\qt_functions.prf:
c:\Qt\4.8.4.1\mkspecs\features\qt_config.prf:
c:\Qt\4.8.4.1\mkspecs\features\exclusive_builds.prf:
c:\Qt\4.8.4.1\mkspecs\features\default_pre.prf:
c:\Qt\4.8.4.1\mkspecs\features\win32\default_pre.prf:
c:\Qt\4.8.4.1\mkspecs\features\release.prf:
c:\Qt\4.8.4.1\mkspecs\features\debug_and_release.prf:
c:\Qt\4.8.4.1\mkspecs\features\default_post.prf:
c:\Qt\4.8.4.1\mkspecs\features\win32\default_post.prf:
c:\Qt\4.8.4.1\mkspecs\features\win32\rtti.prf:
c:\Qt\4.8.4.1\mkspecs\features\win32\exceptions.prf:
c:\Qt\4.8.4.1\mkspecs\features\win32\stl.prf:
c:\Qt\4.8.4.1\mkspecs\features\shared.prf:
c:\Qt\4.8.4.1\mkspecs\features\warn_on.prf:
c:\Qt\4.8.4.1\mkspecs\features\qt.prf:
c:\Qt\4.8.4.1\mkspecs\features\win32\thread.prf:
c:\Qt\4.8.4.1\mkspecs\features\moc.prf:
c:\Qt\4.8.4.1\mkspecs\features\win32\windows.prf:
c:\Qt\4.8.4.1\mkspecs\features\resources.prf:
c:\Qt\4.8.4.1\mkspecs\features\uic.prf:
c:\Qt\4.8.4.1\mkspecs\features\yacc.prf:
c:\Qt\4.8.4.1\mkspecs\features\lex.prf:
c:\Qt\4.8.4.1\mkspecs\features\include_source_dir.prf:
c:\Qt\4.8.4.1\lib\qtmain.prl:
qmake: qmake_all FORCE
	@$(QMAKE) -spec c:\Qt\4.8.4.1\mkspecs\win32-g++ CONFIG+=release -o Makefile Lab2_server.pro

qmake_all: FORCE

make_default: release-make_default debug-make_default FORCE
make_first: release-make_first debug-make_first FORCE
all: release-all debug-all FORCE
clean: release-clean debug-clean FORCE
distclean: release-distclean debug-distclean FORCE
	-$(DEL_FILE) Makefile

check: first

release-mocclean: $(MAKEFILE).Release
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean: $(MAKEFILE).Debug
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables: $(MAKEFILE).Release
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables: $(MAKEFILE).Debug
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile
