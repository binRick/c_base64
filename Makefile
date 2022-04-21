BUILD_DIR = .build
GC = git clone --recurse-submodules
GET_COMMIT = "git log -q |grep '^commit '|head -n1|cut -d' ' -f2"

default: all

.PHONY: all

all: build test

.PHONY: .FORCE
.FORCE:

dependencies: base252 objectively

clib-install:
	@clib install

setup: clib-install

build: dependencies
	@test -d $(BUILD_DIR) && {  meson $(BUILD_DIR) --reconfigure; } || { meson $(BUILD_DIR); }

test:
	@meson test -C $(BUILD_DIR) --verbose

clean:
	@test -d $(BUILD_DIR) && rm -rf $(BUILD_DIR)

install:
	@echo Install OK

tidy:
	@./tidy.sh

pull: git-pull clib build test

clib-update:
	@./update_commit.sh

objectively:
	@[[ -d deps/Objectively ]] || $(GC) https://github.com/jdolan/Objectively deps/Objectively
	@cd deps/Objectively && git pull
	@cd deps/Objectively && [[ -f configure ]] || autoreconf -i
	@cd deps/Objectively && [[ -f Makefile ]] || ./configure
	@cd deps/Objectively && make -j

base252:
	@[[ -d deps/base252 ]] || $(GC) https://github.com/scandum/base252 deps/base252
	@cd deps/base252 && git pull
	@cd deps/base252 && gcc -lz -o test test.c && ./test

git-pull:
	@git pull

git-commit:
	@git commit -am 'automated git commit'

push: tidy git-commit
	@git push
