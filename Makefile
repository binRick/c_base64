BUILD_DIR = .build
GC = git clone --recurse-submodules
GET_COMMIT = "git log -q |grep '^commit '|head -n1|cut -d' ' -f2"

default: all

.PHONY: all

all: build test

.PHONY: .FORCE
.FORCE:

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

dependencies:
	@[[ -d deps/base252 ]] || $(GC) https://github.com/scandum/base252 deps/base252
	@cd deps/base252 && git pull
	@cd deps/base252 && gcc -lz -o test test.c && ./test

git-pull:
	@git pull

git-commit:
	@git commit -am 'automated git commit'

push: tidy git-commit
	@git push
