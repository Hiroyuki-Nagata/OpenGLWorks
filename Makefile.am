# subdirectories
SUBDIRS = c1-1 c1-2 cube oct round vertex-array

# chain with ChangeLog
dist-hook: ChangeLog

# work when configure.ac is updated
ChangeLog: configure.ac
	git log --stat --name-only --date=short --abbrev-commit > ChangeLog
